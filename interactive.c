#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"
#include "scheduler.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <FIFO/SJF> <job_sizes_comma_separated> \n", argv[0]);
        return 1;
    }
    
    char *type = (argv[1]);
    char *jobs_str = argv[2];

    int jobs[100];
    int count = 0;

    char *tok = strtok(jobs_str, ",");

    while(tok != NULL)
    {
        int value = atoi(tok);
        jobs[count] = value;
        count++;
        tok = strtok(NULL, ",");
    }

    if(strcmp(type, "SJF") == 0){
        SJF(jobs, count);
    }
    else{
        FIFO(jobs, count);
    }

    return 0;
}