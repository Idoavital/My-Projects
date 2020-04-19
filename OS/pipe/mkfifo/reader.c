#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
	int i=10;
    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];
   /* char * myfifo2 = "/tmp/myfifo2";
    char buf2[MAX_BUF];*/

while(i--)
{
    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    
    printf("Received: %s\n", buf);
    close(fd);
    
    printf("reader send yaa \n");
    fd = open(myfifo, O_WRONLY);
    write(fd, "yaaa", sizeof("Hi"));
    close(fd);
}
    return 0;
}


