#Created by: Benjamin Olsen
#Curtin Student Number: 19481681
#Purpose: To act as the makefile for the COMP2006 Operating Systems 2019 Semester 1 Assignment

CC=gcc
CFLAGS= -Wall -pedantic -ansi -g -c -Werror
MATH= -lm
OBJ= linkedlist.o io.o scheduler.o
GOBJ = generator.o
OUT= scheduler
GOUT= generator

default: Scheduler Generator
Generator: $(GOBJ)
	$(CC) $(GOBJ) -o $(GOUT)
	./generator
$(GOBJ): generator.c
	$(CC) $(CFLAGS) generator.c
Scheduler: $(OBJ)
	$(CC) $(OBJ) -pthread -o $(OUT)
scheduler.o: scheduler.c scheduler.h io.h linkedlist.h
	$(CC) $(CFLAGS) scheduler.c
io.o: io.c io.h linkedlist.h scheduler.h
	$(CC) $(CFLAGS) io.c
linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) linkedlist.c
clean:
	rm *.o $(OUT) $(GOUT) task_file
	clear
