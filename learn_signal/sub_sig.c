#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

void sign_handle(int signum){
    printf("I'm SIGINT\n");
    //exit(EXIT_SUCCESS);
}

void my_custom_default_signal(int signum){
    printf("hello Tuan\n");
}


int main(int argc,const char *argv[]){
    sigset_t newset,oldset;

    

    //signal(SIGINT,sign_handle);
    signal(SIGUSR1,my_custom_default_signal);
    sigemptyset(&newset);
    sigemptyset(&oldset);
    sigaddset(&newset,SIGINT);
    if(sigprocmask(SIG_SETMASK,&newset,&oldset) == 0){
        if(sigismember(&newset,SIGINT) == 1){
            printf("SIGINT was blocked\n");
        }else{
            printf("SIGINT wasn't blocked\n");
        }
    }
    while(1){

    }
    return 0;
}

