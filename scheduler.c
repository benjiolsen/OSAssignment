/*
Created by: Benjamin Olsen
Student Number: 19481681
Purpose: To act as the file which contains all the functions to act as a cpu
         scheduler for the 2019 Operating Systems assignment. The Scheduler
         is a FIFO scheduler which acts to executes the tasks in the order
         they are recieved
*/

int main(int argv,char** argc){
    /* Calls validate to validate and start the program */
    validate(argv,argc);
    return 0;
}

void validate(int argv,char** argc){
    /* Creates the pointer to the struct for sharing the variables */
    shared* share;
    int ii;
    /* The malloc places the struct on the heap, meaning it shall be shared
       across the threads */
    share = (shared*)malloc(sizeof(shared));
    if(argv==3){
        /* ensure that there are 2 arguments alongside the running of the
           program */
        if(strcmp(argc[1],"task_file\0")==0){            }
            /* Ensures that the second argument is the task file */
            if(!((atoi(argc[2])<1)||(atoi(argc[2])>10))){
                /* Ensures the next argument is in the correct range */
                /* Makes an empty ready queue using the functions in
                   linkedlist.c, using the specified max size */
                share->ready_queue = makeEmpty(atoi(argc[2]));
                /* Ensures the shared variable contains the max size
                   of the queue */
                share->max=atoi(argc[2]);
                /* Initialises the mutex and condition variables */
                pthread_mutex_init(&(share->mutex),NULL);
                pthread_cond_init(&(share->full),NULL);
                pthread_cond_init(&(share->empty),NULL);
                /* Initialises the flag variable to say that it hasnt been
                   completed yet */
                share->flag=0;

                /* Creates the first thread, task(), passing it the struct
                   of share, and creating it with defualt behaviour */
                pthread_create(&(share->thread_id[0]),NULL,&task,share);
                /* Loops through, creating the CPU threads */
                for(ii=1;ii<NUM_THREADS;ii++){
                    pthread_create(&(share->thread_id[ii]),NULL,&cpu,share);
                }
                /* Waits for each thread to exit and then joins them */
                for(ii=0;ii<NUM_THREADS;ii++){
                    pthread_join((share->thread_id[ii]),NULL);
                }
                /* Frees the ready queue */
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
}
void* cpu(void* vshare){
    /* Creates the temp variables to store the pid and burst*/
    int pid,burst;
    /* A temporary variable, local to the specific CPU, so that the exact
       thread may be distinguished later on */
    pthread_t temp;
    /* Loop variable */
    int ii = 0;
    /* Created to typecast the void* that is the parameter */
    shared* share;
    /* Gets the PID of the thread */
    temp = pthread_self();
    /* Typecasts the void* parameter */
    share = (shared*)vshare;
    /* Loops until the ready queue is empty, or the flag isnt 0 anymore */
    while(share->ready_queue->count!=0||share->flag==0){
        /* Obtains the lock on the mutex to ensure mutual exclusion */
        pthread_mutex_lock(&(share->mutex));
        /* Whilst the ready queue is empty, wait until signalled */
        while(share->ready_queue->count==0&&share->flag==0){
            pthread_cond_wait(&(share->full),&(share->mutex));
        }
        if(share->ready_queue->count!=0){
            /* If the queue isnt empty, execute the code */
            /* Set the temp variables */
            pid = share->ready_queue->head->pid;
            burst = share->ready_queue->head->burstTime;
            /* Deletes the item it just read from */
            deleteFirst(share->ready_queue);
            /* Calls sleep to simulate execution */
            sleep(burst/100);
            for(ii=1;ii<NUM_THREADS;ii++){
                /* Loop and if statement determines which CPU executed */
                if(temp==share->thread_id[ii]){
                    printf("CPU #%d executed task #%d for: %ds\n",ii,pid,burst);
                }
            }
        }
        /* Signals that the queue was emptied */
        pthread_cond_signal(&(share->empty));
        /* Unlocks the mutex lock */
        pthread_mutex_unlock(&(share->mutex));
    }
    return NULL;
}

void* task(void* vshare){
    /* Creates the linked list that will be filled from the file */
    LinkedList* fileList;
    /* Ready for typecasting */
    shared* share;
    /* Type-Casts */
    share = (shared*)vshare;
    /* Creates and empty list for the file, with the 100 tasks in it */
    fileList = makeEmpty(100);
    /* Calls readLines from the file IO to read the pid and burst from the
       task file */
    readLines(fileList,"task_file");
    /* Loops until it sets the flag that says the file list is empty */
    while(share->flag==0){
        /* Gains a lock to ensure mutual exclusion */
        pthread_mutex_lock(&(share->mutex));
        while(share->ready_queue->count>=share->max){
            /* Spinlocks until the cpu task executes the signal call */
            pthread_cond_wait(&(share->empty),&(share->mutex));
        }
        if(fileList->count>=2&&share->max>=2){
            /* If the file has more than 2 things in it, and the ready queue
               can take 2 or more things */
            /* Inserts into the ready queue from the file queue */
            insertLast(share->ready_queue,fileList->head->pid,fileList->head->burstTime);
            /* Deletes from the file queue */
            deleteFirst(fileList);
            insertLast(share->ready_queue,fileList->head->pid,fileList->head->burstTime);
            deleteFirst(fileList);
            if(share->ready_queue->count==share->max||fileList->count==0){
                /* If the ready queue is full or the file is empty, then signal
                   to the CPU threads */
                pthread_cond_signal(&(share->full));
            }
        }else if(fileList->count>=2&&share->max==1){
            /* If the file has more than two things, yet the queue cant take
               2 or more, just take the one at a time, and signal its full */
            insertLast(share->ready_queue,fileList->head->pid,fileList->head->burstTime);
            deleteFirst(fileList);
            pthread_cond_signal(&(share->full));
        }else if(fileList->count==1){
            /* Else, if theres only one thing in the file, take it out */
            insertLast(share->ready_queue,fileList->head->pid,fileList->head->burstTime);
            deleteFirst(fileList);
            pthread_cond_signal(&(share->full));
        }else if(fileList->count==0){
            /* If the file list is empty, set the flag to say it is, and then
               signal so the cpus can exit their waits if needed*/
            share->flag=1;
            pthread_cond_signal(&(share->full));
        }
        /* Unlocks the mutex lock */
        pthread_mutex_unlock(&(share->mutex));
    }
    /* Frees the list of items in the file */
    freeList(fileList);
    /* Broadcasts to all threads that the the full condition is free */
    pthread_cond_broadcast(&(share->full));
    return NULL;
}
