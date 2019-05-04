#include "scheduler.h"

int main(int argv,char** argc){
    validate(argv,argc);
    return 0;
}

void validate(int argv,char** argc){
    shared* share;
    int ii;
    share = (shared*)malloc(sizeof(shared));
    if(argv==3){
        if(strcmp(argc[1],"task_file\0")==0){
                if(!((atoi(argc[2])<1)||(atoi(argc[2])>10))){
                    share->ready_queue = makeEmpty(atoi(argc[2]));
                    share->times=0;
                    pthread_mutex_init(&(share->mutex),NULL);
                    pthread_cond_init(&(share->full),NULL);
                    pthread_cond_init(&(share->empty),NULL);
                    pthread_create(&(share->thread_id[0]),NULL,&task,share);
                    for(ii=0;ii<3;ii++){
                        pthread_create(&(share->thread_id[ii+1]),NULL,&cpu,share);
                    }
                    for(ii=0;ii<NUM_THREADS-1;ii++){
                        pthread_join((share->thread_id[ii]),NULL);
                    }
                    freeList(share->ready_queue);
                }else{
                    fprintf(stderr,"Please run as ./scheduler task_file m\n");
                    fprintf(stderr,"Where m is the maximum size of the ready queue (1-10)\n");
                }
        }else{
            fprintf(stderr,"Please run as ./scheduler task_file m\n");
            fprintf(stderr,"Where m is the maximum size of the ready queue (1-10)\n");
        }
    }else{
        fprintf(stderr,"Please run as ./scheduler task_file m\n");
        fprintf(stderr,"Where m is the maximum size of the ready queue (1-10)\n");
    }
    free(share);
    /*pthread_mutex_destroy(&(share->mutex));
    pthread_cond_destroy(&(share->full));
    pthread_cond_destroy(&(share->empty));*/
}
void* cpu(void* vshare){
    shared* share;
    share = (shared*)vshare;
    for(;;){
        pthread_mutex_lock(&(share->mutex));
        while(share->ready_queue->count==0){
            pthread_cond_wait(&(share->full),&(share->mutex));
        }
        share->ready_queue->count--;
        printf("%d %ld\n",share->ready_queue->count,pthread_self());
        pthread_mutex_unlock(&(share->mutex));
        pthread_cond_signal(&(share->empty));
    }

}

void* task(void* vshare){
    shared* share;
    share = (shared*)vshare;
    for(;;){
        pthread_mutex_lock(&(share->mutex));
        while(share->ready_queue->count>0){
            pthread_cond_wait(&(share->empty),&(share->mutex));
        }
        share->ready_queue->count++;
        share->ready_queue->count++;
        share->times++;
        pthread_cond_signal(&(share->full));
        pthread_mutex_unlock(&(share->mutex));
    }
}
