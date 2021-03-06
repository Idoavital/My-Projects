/*
 * buse - block-device userspace extensions
 * Copyright (C) 2013 Adam Cozzette
 *
 * This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#include "buse.h"

enum {READ , WRITE };
/*
 * These helper functions were taken from cliserv.h in the nbd distribution.
 */
static int sk ;

struct buse_all
{
    struct buse_req request;
    struct nbd_reply reply;
}__attribute__((packed));

#ifdef WORDS_BIGENDIAN
u_int64_t ntohll(u_int64_t a) {
  return a;
}
#else
u_int64_t ntohll(u_int64_t a) {
  u_int32_t lo = a & 0xffffffff;
  u_int32_t hi = a >> 32U;
  lo = ntohl(lo);
  hi = ntohl(hi);
  return ((u_int64_t) lo) << 32U | hi;
}
#endif
#define htonll ntohll

static int read_all(int fd, char* buf, size_t count)
{
  int bytes_read;

  while (count > 0) {
    bytes_read = read(fd, buf, count);
    assert(bytes_read > 0);
    buf += bytes_read;
    count -= bytes_read;
}
  assert(count == 0);

  return 0;
}

static int write_all(int fd, char* buf, size_t count)
{
  int bytes_written;

  while (count > 0) {
    bytes_written = write(fd, buf, count);
    assert(bytes_written > 0);
    buf += bytes_written;
    count -= bytes_written;
  }
  assert(count == 0);

  return 0;
}

 void buseDone(struct buse_req *req_st , int status) /*my functions*/
{
    switch (status)
    {
    case READ:
        write_all(sk, (char*)((struct buse_all*)req_st)->request , sizeof(struct nbd_reply) + req_st->len);
     break;
    case WRITE:
        write_all(sk, (char*)((struct buse_all*)req_st)->request , sizeof(struct nbd_reply));
     break;
    }

}

int buse_main(const char* dev_file, const struct buse_operations *aop, void *userdata)
{
  int sp[2];
  int nbd, err, tmp_fd;
  u_int64_t from;
  u_int32_t len;
  ssize_t bytes_read;
  struct nbd_request request;
  struct buse_all* main_buse;


  err = socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
  assert(!err);

  nbd = open(dev_file, O_RDWR);
  if (nbd == -1) {
    fprintf(stderr,
        "Failed to open `%s': %s\n"
        "Is kernel module `nbd' is loaded and you have permissions "
        "to access the device?\n", dev_file, strerror(errno));
    return 1;
  }

  if (aop->blksize) {
    err = ioctl(nbd, NBD_SET_BLKSIZE, aop->blksize);
    assert(err != -1);
  }
  if (aop->size) {
    err = ioctl(nbd, NBD_SET_SIZE, aop->size);
    assert(err != -1);
  }
  if (aop->size_blocks) {
    err = ioctl(nbd, NBD_SET_SIZE_BLOCKS, aop->size_blocks);
    assert(err != -1);
  }

  err = ioctl(nbd, NBD_CLEAR_SOCK);
  assert(err != -1);

  if (!fork()) {
    /* The child needs to continue setting things up. */
    close(sp[0]);
    sk = sp[1];

    if(ioctl(nbd, NBD_SET_SOCK, sk) == -1){
      fprintf(stderr, "ioctl(nbd, NBD_SET_SOCK, sk) failed.[%s]\n", strerror(errno));
    }
#if defined NBD_SET_FLAGS && defined NBD_FLAG_SEND_TRIM
    else if(ioctl(nbd, NBD_SET_FLAGS, NBD_FLAG_SEND_TRIM) == -1){
      fprintf(stderr, "ioctl(nbd, NBD_SET_FLAGS, NBD_FLAG_SEND_TRIM) failed.[%s]\n", strerror(errno));
    }
#endif
    else{
      err = ioctl(nbd, NBD_DO_IT);
      fprintf(stderr, "nbd device terminated with code %d\n", err);
      if (err == -1)
	fprintf(stderr, "%s\n", strerror(errno));
    }

    ioctl(nbd, NBD_CLEAR_QUE);
    ioctl(nbd, NBD_CLEAR_SOCK);

    exit(0);
  }

  /* The parent opens the device file at least once, to make sure the
   * partition table is updated. Then it closes it and starts serving up
   * requests. */

  tmp_fd = open(dev_file, O_RDONLY);
  assert(tmp_fd != -1);
  close(tmp_fd);

  close(sp[1]);
  sk = sp[0];



  while ((bytes_read = read(sk, &request, sizeof(request))) > 0)
  {
    len = ntohl(request.len);
    from = ntohll(request.from);
    assert(bytes_read == sizeof(request));

    main_buse = (struct buse_all *) malloc(sizeof(struct buse_all )+len);
    memcpy(main_buse->reply.handle, request.handle, sizeof(main_buse->reply.handle));

    main_buse->reply.error = htonl(0);
    main_buse->reply.magic = htonl(NBD_REPLY_MAGIC);

    main_buse->request.len =len;
    main_buse->request.offset = from;
    main_buse->request.data = (char*)main_buse + sizeof(struct buse_req) + sizeof(struct nbd_reply);


    assert(request.magic == htonl(NBD_REQUEST_MAGIC));

    switch(ntohl(request.type)) {
      /* I may at some point need to deal with the the fact that the
       * official nbd server has a maximum buffer size, and divides up
       * oversized requests into multiple pieces. This applies to reads
       * and writes.
       */
    case NBD_CMD_READ:
      fprintf(stderr, "Request for read of size %d\n", len);
      /* Fill with zero in case actual read is not implemented */

      if (aop->read)
      {
        main_buse->reply.error = aop->read(&main_buse->request, userdata);
      }
      else
      {
        /* If user not specified read operation, return EPERM error */
        main_buse->reply.error = htonl(EPERM);
      }

      break;
    case NBD_CMD_WRITE:
      fprintf(stderr, "Request for write of size %d\n", len);

      read_all(sk, (char*)main_buse->request.data, main_buse->request.len);
      if (aop->write)
      {
        main_buse->reply.error = aop->write(&main_buse->request, userdata);
      }
      else
      {
        /* If user not specified write operation, return EPERM error */
        main_buse->reply.error = htonl(EPERM);
      }

     /* write_all(sk, (char*)&(main_buse->reply), sizeof(struct nbd_reply));*/
      break;
    case NBD_CMD_DISC:
      /* Handle a disconnect request. */
      if (aop->disc) {
        aop->disc(userdata);
      }
      return 0;
#ifdef NBD_FLAG_SEND_FLUSH
    case NBD_CMD_FLUSH:
      if (aop->flush) {
        main_buse->reply.error = aop->flush(userdata);
      }
      write_all(sk, (char*)&main_buse->reply, sizeof(struct nbd_reply));
      break;
#endif
#ifdef NBD_FLAG_SEND_TRIM
    case NBD_CMD_TRIM:
      if (aop->trim) {
        main_buse->reply.error = aop->trim(from, len, userdata);
      }
      write_all(sk, (char*)&main_buse->reply, sizeof(struct nbd_reply));
      break;
#endif
    default:
      assert(0);
    }
  }
  if (bytes_read == -1)
    fprintf(stderr, "%s\n", strerror(errno));
  return 0;
}
