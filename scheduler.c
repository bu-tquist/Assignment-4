#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}


float SJF(int* jobs, int size) {
   float totalTime = 0.0;

   int* sorted =  (int*)malloc(size * sizeof(int));
   
   for(int i = 0; i < size; i++){
    sorted[i] = jobs[i];
   }

   qsort(sorted, size, sizeof(int), compare_ints);
    for(int i = 0; i < size; i++){
        totalTime += do_job(sorted[i], sorted[i], sorted[i], 0);
    }
    free(sorted);
    return totalTime/size;
}

float FIFO(int* jobs, int size) {
    float totalTime = 0.0;

    float current_time = 0.0;

    for(int i = 0; i < size; i++){
        totalTime += current_time;
        float duration = do_job(jobs[i], jobs[i], jobs[i], 0);
        current_time += duration;
    }
    return totalTime/size;
}
