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
   printf("execv start\n");
   char *args[] = {"ls", "-l", NULL};
   //execv("/bin/ls", args);
   printf("execl start\n");
   //execl("/bin/ls", "ls", "-l", NULL);
   printf("execlp start\n");
   execlp("ls", "ls", "-l", NULL);// look command from env
   printf("hello, I am child (pid:%d)\n", (int)getpid());
 } else {
   int wc = wait(NULL);
   printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
 }
 return 0;
}
