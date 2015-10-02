/* A simple test harness for memory alloction. */

#include "mm_alloc.h"
#include <stdio.h>
int main(int argc, char **argv)
{
    int* data;
    int* data2;
    int* data3;

    data = (int*) mm_malloc(4);
    data2 = (int*) mm_malloc(4);
    data3 = (int*) mm_malloc(4);
    
    mm_free(data);
    data = NULL;
    mm_free(data2);
    data2 = NULL;
    mm_free(data3);
    data3 = NULL;
    
    data = (int*) mm_malloc(8);
    data2 = (int*) mm_malloc(4);
    
    printf("malloc sanity test successful!\n");
    return 0;
}
