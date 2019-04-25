#ifndef SCHEDULER_H
    #define SCHEDULER_H
    #include <time.h>
    #include <pthread.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include "io.h"
    #include "linkedlist.h"

    #define TRUE 0
    #define FALSE !TRUE
    struct cpuTask {
        int placeHolder;
    } cpuTask;

    void start(int,char**);
    void cpu();
    void task();
#endif
