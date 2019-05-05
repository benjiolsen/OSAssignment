/*
Created by: Benjamin Olsen
Student Number: 19481681
Purpose: To act as the header file for the scheduler c file. Contains the
         stuct for the cpuTask, and all the predeclerations for the functions used.
         Also all the includes needed for the scheduler.c file to function.
*/
#ifndef SCHEDULER_H
    /* Defines a header guard to avoid multiple includes */
    #define SCHEDULER_H
    #include <time.h>
    #include <pthread.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include "io.h"
    #include "linkedlist.h"

    /* Defines true and false for later use in the program */
    #define FALSE 0
    #define TRUE !FALSE

    /* Defines the amount of threads. Three cpu() and one task() */
    #define NUM_THREADS 4

    /* Defines the struct cpuTask, so that it can be used to store all the
       information relating to the arrival, waiting, burst time, etc. */
    typedef struct{
        int placeHolder;
    }cpuTask;

    typedef struct{
        LinkedList* ready_queue;
        pthread_t thread_id[NUM_THREADS];
        pthread_mutex_t mutex;
        pthread_cond_t full;
        pthread_cond_t empty;
        int max;
        int flag;
    }shared;

    /* Acts to start the program by ensuring the user entered the args correctly
       then calls the needed submodules */
    void validate(int,char**);
    /* Simulates the cpu's executing tasks and their critical sections */
    void* cpu(void* vshare);
    /* Reads in tasks from the file and places them into the ready queue */
    void* task(void* vshare);
#endif
