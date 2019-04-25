#include "scheduler.h"
int main(int argv,char** argc){
    if(argv==3){
        start(argv,argc);
    }
    else{
        fprintf(stderr,"Please run as ./scheduler task_file m\n");
        fprintf(stderr,"Where m is the maximum size of the ready queue (1-10)\n");
    }
    return 0;
}

void start(int argv,char** argc){
    if(strcmp(argc[1],"task_file\0")==0){
            if(!((atoi(argc[2])<1)||(atoi(argc[2])>10))){
                /* Functionality yet to be implmented */
            }else{
                fprintf(stderr,"Please run as ./scheduler task_file m\n");
                fprintf(stderr,"Where m is the maximum size of the ready queue (1-10)\n");
            }
    }else{
        fprintf(stderr,"Please run as ./scheduler task_file m\n");
        fprintf(stderr,"Where m is the maximum size of the ready queue (1-10)\n");
    }
}
void cpu(){

}

void task(){

}
