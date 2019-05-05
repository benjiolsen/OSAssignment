/*
Created by: Benjamin Olsen
Student Number: 19481681
Purpose: To act as the header file for the io c file. Contains the all the
         predeclerations for the functions used. Also all the includes needed
         for the io.c file to function.
*/
#ifndef IO_H
    /* Defines a header guard to avoid multiple includes */
    #define IO_H

    #include "linkedlist.h"
    #include "scheduler.h"

    /* Defines the buffer used for fgets when reading from the file */
    #define BUFFER_SIZE 1024
    /* Reads in the lines from the specified file, into a linked list */
    int readLines(LinkedList* list,char* filename);
#endif
