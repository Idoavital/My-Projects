#define _BSD_SOURCE
#define _POSIX_C_SOURCE 199309L /*sig info*/

#include <sys/types.h>
 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
#include <semaphore.h>



 /* Read characters from the pipe and echo them to stdout. */
sem_t sem;
 void
 read_from_pipe (int file)
 {
  
   FILE *stream;
   int c;
  
     stream = fdopen (file, "r");
     while ((c = fgetc (stream)) != EOF)
     putchar (c);
     fclose (stream);
 }

 /* Write some random text to the pipe. */

 void write_to_pipe (int file)
 {
   FILE *stream;
  
    stream = fdopen (file, "w");
    fprintf (stream, "ping!\n");
    fflush(stream);
    fclose (stream);
 }
 
 void write_pong (int file)
 {
    FILE *stream;
    stream = fdopen (file, "w");
    fprintf (stream, "pong, !\n");
    fflush(stream);
    fclose (stream);
 }
 


 int
 main (void)
 {
   pid_t pid;
   int mypipe[2];
   int pipe_2[2];

   sem_init (&sem, 1 ,1);
   /* Create the pipe. */
   if (pipe (mypipe))
     {
       fprintf (stderr, "Pipe failed.\n");
       return EXIT_FAILURE;
     }
   
   if (pipe (pipe_2))
     {
       fprintf (stderr, "Pipe failed.\n");
       return EXIT_FAILURE;
     }

   /* Create the child process. */
   pid = fork ();
   if (pid == (pid_t) 0)
     {
       /* This is the child process.
          Close other end first. */
       sleep(3);
       int i =10;
       while (i--)
         {
           printf("i =%d\n",i);
           sem_wait (&sem);
           close (mypipe[1]);
           read_from_pipe (mypipe[0]);
            
           close (pipe_2[0]);
           write_pong (pipe_2[1]);
           
           sem_post (&sem);
         }
       return EXIT_SUCCESS;
     }
   else if (pid < (pid_t) 0)
     {
       /* The fork failed. */
       fprintf (stderr, "Fork failed.\n");
       return EXIT_FAILURE;
     }
   else
     {
       /* This is the parent process.
          Close other end first. */
        int i =10;
       while (i--)
         {
            sem_wait (&sem);
            close (mypipe[0]);
            write_to_pipe (mypipe[1]);
            close (mypipe[1]);
            
             sleep(1);
              
           close (pipe_2[1]);
           read_from_pipe (pipe_2[0]);
           sem_post (&sem);
          
         }   
       return EXIT_SUCCESS;
     }
 }