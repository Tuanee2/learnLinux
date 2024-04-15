#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_t tid1 ,tid2 ;

typedef struct{
    char name[30];
    int yearOfBirth;
    char phone_number[11];
    char hometown[30];
} human;

static void *thr_hanlder(void *args){
    pthread_t tid = pthread_self();
    human *data = (human *)args;

    if(pthread_equal(tid,tid1)){
        printf("I'm thread 1.\n");
        
    }else{
        printf("Print information :\n");
        printf("Name : %s\n",data->name);
        printf("Nam sinh : %d\n",data->yearOfBirth);
        printf("Phone number : %s\n",data->phone_number);
        printf("Hometown : %s\n",data->hometown);
        
    }
    //pthread_detach(pthread_self());
}


int main(int argc,const char *argv[]){
    int ret;

    human thread_data = {0};
    strncpy(thread_data.name,"Bui Quoc Tuan",sizeof(thread_data.name));
    thread_data.yearOfBirth = 2002;
    strncpy(thread_data.phone_number,"0982181002",sizeof(thread_data.phone_number));
    strncpy(thread_data.hometown,"Thai Binh",sizeof(thread_data.hometown));

    if(ret = pthread_create(&tid1,NULL,&thr_hanlder,NULL)){
        printf("Creating thread is error !!!\n");
        return -1;
    }

    sleep(2);

    if(ret = pthread_create(&tid2,NULL,&thr_hanlder,&thread_data)){
        printf("Creating thread is error !!!\n");
        return -1;
    }
    pthread_join(tid1, NULL);
    printf("thread 1 is terminated\n");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}