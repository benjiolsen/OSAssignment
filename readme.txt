NAME: Benjamin Olsen
STUDENT NUMBER: 19481681
DATE: 06/05/2019
UNIT: COMP2006 Operating Systems
PROGRAM: Scheduler
PURPOSE: To emulate a FIFO CPU scheduler in the C programming language, using the POSIX threads library.

RUNNING:
    TO run this program, the corresponding c files must be compiled.

    Ensuring the program 'make' and the compiler 'gcc' is installed on your system, run the command 'make'
    This should compile, link, and create two programs.
    The first of which, is a quickly written generator for the task file, written in the C language.
    This is then immediately run, which generates a new, random task file, to the assignment spec.
    This program can be run at any time the user wishes, so long as the scheduler program is not running concurrently.
    A new task file will be generated each time it is run.

    The other program which is created, is the scheduler. This is the program which is made for the assignment.
    As per the assignment specifications, it must be run in the format;
        './scheduler task_file m'
    where m is a number between 1 and 10, inclusive.
