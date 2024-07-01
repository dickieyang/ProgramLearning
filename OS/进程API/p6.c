#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
 printf("hello world (pid:%d)\n", (int)getpid());
 int fd = open("./p6.out", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
 if (fd == -1) {
   printf("open file failed.\n");
   return 1;
 }
 int rc = fork();
 if(rc < 0) {
   fprintf(stderr, "fork failed\n");
 } else if(rc == 0) {
   char buf[1024] = {"I don't know say what is right.\n"};
   int len = write(fd, buf, strlen(buf));
   printf("child write len:%d\n", len);
   printf("hello, I am child (pid:%d)\n", (int)getpid());
 } else {
   char buf[1024] = {"I'm parent hahah anything else?\n"};
   //int wc = waitpid(-1, NULL, 0); //equals to wait(NULL); 
   int len = write(fd, buf, strlen(buf));
   printf("parent write len:%d\n", len);
   int wc = wait(NULL);
   printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
 }
 return 0;
}
