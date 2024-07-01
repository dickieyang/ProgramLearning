#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
 printf("hello world (pid:%d)\n", (int)getpid());
 int x = 100;
 int rc = fork();
 if(rc < 0) {
   fprintf(stderr, "fork failed\n");
 } else if(rc == 0) {
   printf("child x is %d\n", x);
   x = 200;
   printf("x is %d after child modify\n", x);
   printf("hello, I am child (pid:%d)\n", (int)getpid());
 } else {
   printf("parent x is %d\n", x);
   x = 300;
   printf("x is %d after parent modify\n", x);
   int wc = wait(NULL);
   printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
 }
 return 0;
}
