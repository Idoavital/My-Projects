#ifndef	__CIRCBUF_H__
#define	__CIRCBUF_H__

#include <stddef.h> /* size_t */

typedef struct Circ_B CIRC_B;

/* crate a new circular buffer */
CIRC_B *cBufCreate(size_t size);

/* free the memory of pointer */
void cBufDestroy(CIRC_B *cb);

/* Returns number of bytes read */
size_t cBufRead(CIRC_B *cb, void *buf, size_t size);

/* Return number of bytes written */
size_t cBufWrite(CIRC_B *cb, const void *buf, size_t size);

/*check how many free byts are free to write*/
size_t cBufFreeSpace(CIRC_B *cb);

/* Error handling */

typedef enum
{
	__no_data_to_read,
	__buffer_is_full,
	__buffer_overwrite
}CIRC_B_ERROR;

CIRC_B_ERROR Errno;

/* optional assignment */
#ifdef ADVANCED
/* Set status to true to overwrite. Set to false to prevent overwrite. */
void cBufSetOverWrite(CIRC_B *cb, int status);

#endif	/* ADVANCED */

#endif /* __CIRCBUF_H__ */
