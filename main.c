#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  printf("Parent pid: %d\n", getpid());
  int f = fork();
  if(f){
    f = fork();
  }
  if(!f){
    printf("Child pid: %d\n", getpid());
    int y = open("/dev/random", O_RDONLY);
    unsigned int time;
    read(y, &time, 4);
    close(y);
    sleep(time % 15 + 5);
    printf("Child process completed\n");
    return time % 15 + 5;
  }else{
    int status;
    int pid = wait(&status);
    printf("Pid of completed child: %d\nTime child slept: %d seconds\nParent process completed\n", pid, WEXITSTATUS(status));
  }
  return 0;
}
