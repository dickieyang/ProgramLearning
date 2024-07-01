#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
 printf("hello world (pid:%d)\n", (int)getpid());
 int rc = fork();
 if(rc < 0) {
   fprintf(stderr, "fork failed\n");
 } else if(rc == 0) {
   printf("hello, I am child (pid:%d)\n", (int)getpid());
   close(STDOUT_FILENO);
   open("./p4.out", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
   char *myargs[3];
   myargs[0] = strdup("wc");
   myargs[1] = strdup("p4.c");
   myargs[2] = NULL;
   execvp(myargs[0], myargs);
   printf("this shouldn't print out");
 } else {
   int wc = wait(NULL);
   printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
 }
 return 0;
}
