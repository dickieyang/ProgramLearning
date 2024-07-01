#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
 printf("hello world (pid:%d)\n", (int)getpid());
 int fd[2];// create pipe
 if(pipe(fd) == -1) {
   perror("pipe create failed.");
   exit(EXIT_FAILURE);
 }
 int rc = fork();
 if(rc < 0) {
   fprintf(stderr, "fork failed\n");
 } else if(rc == 0) {
   printf("hello, I am child one (pid:%d)\n", (int)getpid());
   char buf[] = "It's data from child one.";
   write(fd[1], buf, sizeof(buf));
   printf("write done.\n");
   exit(0);
 } else {
   int rc2 = fork();
   if(rc2 < 0) {
     perror("fork fail.\n");
     exit(1);
   } else if (rc2 == 0) {
     printf("hello, I am child two (pid:%d)\n", (int) getpid());
     char buf[256];
     read(fd[0], buf, 256);
     printf("read buf:%s\n", buf);
     exit(0);
   }
   int wc = wait(NULL);
   printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
 }
 return 0;
}
