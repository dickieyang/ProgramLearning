#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
 printf("hello world (pid:%d)\n", (int)getpid());
 int rc = fork();
 if(rc < 0) {
   fprintf(stderr, "fork failed\n");
 } else if(rc == 0) {
   printf("hello, I am child (pid:%d)\n", (int)getpid());
 } else {
   int wc = wait(NULL);
   printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
 }
 // Below code always runs in each thread.
 /*
    hello world (pid:133842)
    hello, I am child (pid:133843)
    current pid:133843
    hello, I am parent of 133843 (wc:133843) (pid:133842)
    current pid:133842
  */
 // So, fork() always returns 0 in child-thread context, No matter with method's return value.
 // In parent-thread, fork() will return child's pid.
 printf("current pid:%d\n", getpid());
 return 1;
}
