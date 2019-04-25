#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void){
    
    FILE* taskFile = NULL;
    char outString[25];
    int num,burstTime;

    srand(time(NULL));

    taskFile = fopen("task_file","w");

    if(taskFile==NULL){
        perror("An Error Occured\n");
    }else if(ferror(taskFile)){
        perror("An Error Occured\n");
    }else{
        for(num=1;num<101;num++){
            burstTime = rand() % 49;
            burstTime++;
            sprintf(outString,"%d %d\n",num,burstTime);
            fputs(outString,taskFile);
        }
        fclose(taskFile);
    }
    return 0;
}
