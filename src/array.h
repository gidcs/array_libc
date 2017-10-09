#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_ARRAY
#ifdef DEBUG_ARRAY
    #define __ADEBUG(fmt, args...)    fprintf(stderr, "    [array] "fmt, ## args)
#else
    #define __ADEBUG(fmt, args...)    /* Don't do anything in release builds */
#endif

typedef struct {
    int item_size;
    int item_num;
    int index;
    void *ptr;
} Array;

#define _INITIAL_ITEM_NUM 4
#define _GROWTH_FACTOR 2

int array_init(Array *a, int item_size);
int array_size(Array *a);
void* array_get(Array *a, int index);
int array_push(Array *a, void *item);
void array_free(Array *a);
void array_do_all(Array *a, int (*fptr)(void *, void *), void *params);
