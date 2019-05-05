#include "scheduler.h"

int main(int argv,char** argc){
    validate(argv,argc);
    pthread_exit(NULL);
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
                    share->max=atoi(argc[2]);
                    pthread_mutex_init(&(share->mutex),NULL);
                    pthread_cond_init(&(share->full),NULL);
                    pthread_cond_init(&(share->empty),NULL);
                    share->flag=0;
                    pthread_create(&(share->thread_id[0]),NULL,&task,share);
                    for(ii=1;ii<NUM_THREADS;ii++){
                        pthread_create(&(share->thread_id[ii]),NULL,&cpu,share);
                    }
                    for(ii=0;ii<NUM_THREADS;ii++){
                        pthread_join((share->thread_id[ii]),NULL);
                    }
                    freeList(share->ready_queue);
                    /*pthread_mutex_destroy(&(share->mutex));
                    pthread_cond_destroy(&(share->full));
                    pthread_cond_destroy(&(share->empty));*/
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
    pthread_cond_destroy(&(share->wrt));*/
}
void* cpu(void* vshare){
    int pid,burst;
    pthread_t temp;
    int ii = 0;
    shared* share;
    temp = pthread_self();
    share = (shared*)vshare;
    while(!(share->ready_queue->count==0)||share->flag==0){
        pthread_mutex_lock(&(share->mutex));
        while(share->ready_queue->count==0&&share->flag==0){
            pthread_cond_wait(&(share->full),&(share->mutex));
        }
        if(share->ready_queue->count>0){
            pid = share->ready_queue->head->pid;
            burst = share->ready_queue->head->burstTime;
            sleep(burst/1000);
            for(ii=1;ii<NUM_THREADS;ii++){
                if(temp==share->thread_id[ii]){
                    printf("CPU #%d executed task #%d for: %ds\n",ii,pid,burst);
                }
            }
            deleteFirst(share->ready_queue);
        }
        pthread_cond_signal(&(share->empty));
        /*if(!(share->ready_queue->count==0)){
            pid = share->ready_queue->head->pid;
            burst = share->ready_queue->head->burstTime;
            sleep(burst/1000);
            for(ii=1;ii<NUM_THREADS;ii++){
                if(temp==share->thread_id[ii]){
                    printf("CPU #%d executed task #%d for: %ds\n",ii,pid,burst);
                }
            }
            deleteFirst(share->ready_queue);
            pthread_cond_signal(&(share->empty));
        }*/
        pthread_mutex_unlock(&(share->mutex));
    }
    return NULL;
}

void* task(void* vshare){
    LinkedList* fileList;
    shared* share;
    share = (shared*)vshare;
    fileList = makeEmpty(100);
    readLines(fileList,"task_file");
    while(share->flag==0){
        pthread_mutex_lock(&(share->mutex));
        while(share->ready_queue->count>=share->max){
            pthread_cond_wait(&(share->empty),&(share->mutex));
        }
        if(fileList->count>=2&&share->max>=2){
            insertLast(share->ready_queue,fileList->head->pid,fileList->head->burstTime);
            deleteFirst(fileList);
            insertLast(share->ready_queue,fileList->head->pid,fileList->head->burstTime);
            deleteFirst(fileList);
            pthread_cond_signal(&(share->full));
        }else if(fileList->count>=2&&share->max==1){
            insertLast(share->ready_queue,fileList->head->pid,fileList->head->burstTime);
            deleteFirst(fileList);
            pthread_cond_signal(&(share->full));
        }else if(fileList->count==1){
            insertLast(share->ready_queue,fileList->head->pid,fileList->head->burstTime);
            deleteFirst(fileList);
            pthread_cond_signal(&(share->full));
        }else if(fileList->count==0){
            share->flag=1;
            pthread_cond_signal(&(share->full));
        }
        pthread_mutex_unlock(&(share->mutex));
    }
    freeList(fileList);
    return NULL;
}
