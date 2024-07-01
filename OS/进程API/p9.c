#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
 printf("hello world (pid:%d)\n", (int)getpid());
 int rc = fork();
 if(rc < 0) {
   fprintf(stderr, "fork failed\n");
 } else if(rc == 0) {
   int wc = wait(NULL);
   printf("hello, I am child (wc:%d) (pid:%d)\n", wc, (int)getpid());
 } else {
   int wc = waitpid(0, NULL, 0);
   printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
 }
 return 0;
}
