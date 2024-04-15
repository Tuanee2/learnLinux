#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void signal_hanlder(int signum){
    printf("I'm signal hanlder.\n");
    wait(NULL);
}

int main(int argc,char* argv[]){
    pid_t child_pid;
    child_pid = fork();
    if(child_pid == 0){
        printf("Children process was born, my pid : %d\n",getpid());
        while(1);

    }else{
        signal(SIGCHLD,signal_hanlder);
        printf("Parent process was born, my pid is : %d \n",getpid());
        while(1);
    }
}