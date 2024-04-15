#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;



pthread_t tid1,tid2,tid3;

int ready_to_write = 0;
int ready_to_read = 0;


char *filename = "thongtinsinhvien.txt";

typedef struct{
    char name[30];
    char dateOfBirth[20];
    char homeTown[30];
}student;

int count = 0;


char combinedInfo[200];

static void *thread_hanlde(void *args)
{
    pthread_detach(pthread_self());
    pthread_t tid = pthread_self();
    student *data = (student*)args;

    if(pthread_equal(tid,tid1))
    {
        while(1){
            // lock mutex
            pthread_mutex_lock(&lock1);
            while (ready_to_write != 0) {
                pthread_cond_wait(&cond1, &lock1);
            }
            // write the data        
            printf("Enter name : ");
            fgets(data->name,sizeof(data->name),stdin);
            data->name[strcspn(data->name, "\n")] = 0;
            printf("Enter date of birth : ");
            fgets(data->dateOfBirth,sizeof(data->dateOfBirth),stdin);
            data->dateOfBirth[strcspn(data->dateOfBirth, "\n")] = 0;
            printf("Enter hometown : ");
            fgets(data->homeTown,sizeof(data->homeTown),stdin);
            data->homeTown[strcspn(data->homeTown, "\n")] = 0;

            //
            ready_to_write = 1;
            pthread_cond_signal(&cond2);
            // unlock mutex
            pthread_mutex_unlock(&lock1);
        }
    }
    else if(pthread_equal(tid,tid2))
    {
        while(1){
            // lock mutex
            pthread_mutex_lock(&lock1);
            while (ready_to_write == 0) {
                pthread_cond_wait(&cond2, &lock1);
            }
            
            // combine infomation
            snprintf(combinedInfo, sizeof(combinedInfo), "Name: %s, DateOfBirth: %s, Hometown: %s\n", data->name, data->dateOfBirth, data->homeTown);
            char *ptrInfo = combinedInfo;

            // open the file

            int fd = open(filename, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR );
            if (fd == -1) {
                perror("Can't open the file :((\n");
                exit(EXIT_FAILURE);
            }

            // write data to file
            ssize_t bytes_written = write(fd,ptrInfo,strlen(ptrInfo));
            if(bytes_written == -1)
            {
                perror("error to write data :((");
                exit(EXIT_FAILURE);
            }
            printf("Writting data is completed.\n");

            // close the file
            if (close(fd) == -1) {
                perror("Error to close the file :((\n");
                exit(EXIT_FAILURE);
            }

            ready_to_write = 0;
            ready_to_read =1;
            pthread_cond_signal(&cond3);
        
            // unlock mutex
            pthread_mutex_unlock(&lock1);
        }
    }
    else
    {
        while(1){
            // lock mutex
            pthread_mutex_lock(&lock1);

            while (ready_to_read == 0) {
                pthread_cond_wait(&cond3, &lock1);
            }

            // open the file in only read 
            int fd = open(filename,O_RDONLY);
            if(fd == -1){
                perror("error to open the file :((\n");
                exit(EXIT_FAILURE);
            }

            // read file's data
            char buffer[1024];
            ssize_t bytes_read = read(fd,buffer, sizeof(buffer));
            if(bytes_read == -1){
                perror("error to read data :((\n");
                exit(EXIT_FAILURE);
            }

            // close the file
            if (close(fd) == -1) {
                perror("Error to close the file :((\n");
                exit(EXIT_FAILURE);
            }
            printf("DATA:\n");
            write(STDOUT_FILENO,buffer,bytes_read);
            printf("Continoue write data to file\n");

            ready_to_read = 0;
            pthread_cond_signal(&cond1);
            // unlock mutex
            pthread_mutex_unlock(&lock1);

        }
        
    }
}

int main(int argc,const char* argv[])
{
    int ret;
    student sv1 = {0};

    // create threads
    if(ret = pthread_create(&tid1,NULL,&thread_hanlde,&sv1))
    {
        printf("Error to create the thread 1.\n");
        return -1;
    }

    if(ret = pthread_create(&tid2,NULL,&thread_hanlde,&sv1))
    {
        printf("Error to create the thread 2.\n");
        return -1;
    }

    if(ret = pthread_create(&tid3,NULL,&thread_hanlde,&sv1))
    {
        printf("Error to create the thread 3.\n");
        return -1;
    }
    
    while(1){}

    return 0;
}