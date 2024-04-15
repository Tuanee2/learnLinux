#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char * argv[]){
    int ret;
    int status;
    pid_t child_pid;
    child_pid = fork();
    if(child_pid == 0){
        printf("Im the child process, my PID is : %d\n",getpid());
        printf("My parents process's ID is : %d\n"),getppid();
        printf("I'll terminate after 5 seconds\n");
        while(1);
        //sleep(5);
        exit(0);
    }else{
        ret = wait(&status);
        printf("Im the parents process, my PID is : %d\n",getpid());
        if(WIFEXITED(status)){
            printf("normally termination %d ! status : %d \n",ret,WEXITSTATUS(status));
        }

    }

    return 0;
}