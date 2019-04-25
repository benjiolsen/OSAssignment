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
    /* Defines true and false for later use in programs to ensure an error
       hasn't occured at all */
    #define TRUE 0
    #define FALSE !TRUE

    /* Defines the struct cpuTask, so that it can be used to store all the
       information relating to the arrival, waiting, burst time, etc. */
    typedef struct{
        int placeHolder;
    } cpuTask;

    /* Acts to start the program by ensuring the user entered the args correctly
       then calls the needed submodules */
    void start(int,char**);
    /* Simulates the cpu's executing tasks and their critical sections */
    void cpu();
    /* Reads in tasks from the file and places them into the ready queue */
    void task();
#endif
