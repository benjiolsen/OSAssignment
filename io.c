#include "io.h"

int readLines(LinkedList* list,char* filename)
{
    FILE* taskFile = NULL;
    char buffer[BUFFER_SIZE];
    int pid,burst;
    int failed = FALSE;
    int line = 1;

    taskFile = fopen(filename,"r");
    if(taskFile==NULL)
    {/* Handles the file not existing problem */
        fprintf(stderr,"There was an error opening the file");
        failed = TRUE;

    }
    else if(ferror(taskFile))
    {/* Checks if file is okay to use */
        fprintf(stderr,"There was an error with the file");
        failed = TRUE;
        fclose(taskFile);
    }
    else
    {
        if(fgets(buffer,BUFFER_SIZE,taskFile)!=NULL)
        {/* Attempts to read in the first line, if it cant, runs the else */
            do
            {
                if(sscanf(buffer,"%*s%d %d",burst,pid)==2)
                {
                    insertLast(list,pid,burst);
                }
                else
                {
                    failed = TRUE;
                    fprintf(stderr,"Error on line %d, not in proper format\n",line);
                }
                line++;
            }while((failed == FALSE) && fgets(buffer,BUFFER_SIZE,taskFile)!=NULL);
            /* Cant leave the file being a dangly open boi */
            fclose(taskFile);
        }
        else
        {
            /* fprintf because i don't like it saying Error:Success with
               perror */
            fprintf(stderr,"There was no data in the file\n");
            failed = TRUE;
            /* also close the dangly open boi */
            fclose(taskFile);
        }
    }
    return failed;
}
