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
       information relating to the arrival, service time etc. */
    typedef struct{
        time_t arrive;
        time_t service;
    }cpuTask;

    /* Defines the struct that contains all the variables to be shared
       throughout the threads*/
    typedef struct{
        /* The queue of items */
        LinkedList* ready_queue;
        /* The id of each thread in an array */
        pthread_t thread_id[NUM_THREADS];
        /* The mutex and condition variables for locking/waiting/signalling */
        pthread_mutex_t mutex;
        pthread_cond_t full;
        pthread_cond_t empty;
        /* The total turnaround and waiting time
           doubles are used as that is what timediff return type is*/
        double total_turnaround_time;
        double total_waiting_time;
        /* The max size of the ready queue */
        int max;
        /* The flag variable to exit loop conditions */
        int flag;
        /* The number of tasks completed by each cpu */
        int num_tasks[3];
    }shared;

    /* Acts to start the program by ensuring the user entered the args correctly
       then calls the needed submodules */
    void validate(int,char**);
    /* Simulates the cpu's executing tasks and their critical sections */
    void* cpu(void* vshare);
    /* Reads in tasks from the file and places them into the ready queue */
    void* task(void* vshare);
#endif
