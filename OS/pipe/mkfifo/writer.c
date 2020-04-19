#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>

#define MAX_BUF 1024
int main()
{
	int i =10;
    int fd;
     char buf[MAX_BUF];
    char * myfifo = "/tmp/myfifo";
	
    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

	while(i--)
	{
    /* write "Hi" to the FIFO */
    fd = open(myfifo, O_WRONLY);
    printf("writer send hi \n");
    write(fd, "Hi", sizeof("Hi"));
    close(fd);
    
    sleep(1);
        /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    printf("writer Received : %s\n", buf);
    close(fd);
    
	
    /* remove the FIFO */
   
    /*sleep(1);*/
}
unlink(myfifo);
    return 0;
}
