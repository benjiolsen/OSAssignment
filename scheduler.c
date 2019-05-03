#include "scheduler.h"

LinkedList* ready_queue;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_t thread_id[NUM_THREADS];

int main(int argv,char** argc){
    validate(argv,argc);
    return 0;
}

void validate(int argv,char** argc){
    if(argv==3){
        if(strcmp(argc[1],"task_file\0")==0){
                if(!((atoi(argc[2])<1)||(atoi(argc[2])>10))){
                    ready_queue = makeEmpty(atoi(argc[2]));
                    /* Functionality yet to be implmented */
                }else{
                    fprintf(stderr,"Please run as ./scheduler task_file m\n");
                    fprintf(stderr,"Where m is the maximum size of the ready queue (1-10)\n");
                }
        }else{
            fprintf(stderr,"Please run as ./scheduler task_file m\n");
            fprintf(stderr,"Where m is the maximum size of the ready queue (1-10)\n");
        }
    else{
        fprintf(stderr,"Please run as ./scheduler task_file m\n");
        fprintf(stderr,"Where m is the maximum size of the ready queue (1-10)\n");
    }
    freeList(ready_queue);
}
void cpu(void* ptr){
    pthread_mutex_lock(&mutex);
    while(isEmpty(ready_queue)){
        pthread_cond_wait(&condition,&mutex);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void task(void* ptr){
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
