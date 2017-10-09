#include <stdio.h>
#include "src/array.h"

#define DEBUG_MAIN
#ifdef DEBUG_MAIN
    #define __MDEBUG(fmt, args...)    fprintf(stderr, "[main] "fmt, ## args)
#else
    #define __MDEBUG(fmt, args...)    /* Don't do anything in release builds */
#endif

typedef struct{
    int first;
    int second;
} Item;

#define MAX 10

int print_item(void *item, void *params){
    Item *p = (Item *)item;
    printf("(%d,%d) ", p->first, p->second);
    return 0;
}

int find_item(void *item, void *params){
    Item *p = (Item *)item;
    int *f = (int *)params;
    if(p->first == *f){
        printf("(%d, %d) is found with first=%d.\n",
                p->first, p->second, *f);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]){
    Item temp;
    int i;
    int ret;
    Array a1, a2;
    __MDEBUG("init a\n");
    ret = array_init(&a1, sizeof(Item));
    if(-1 == ret){
        return -1;
    }
    ret = array_init(&a2, sizeof(Item));
    if(-1 == ret){
        return -1;
    }
    printf("\n");
    for(i = 0; i <= MAX; i++){
        temp.first=i;
        temp.second=i*2;
        __MDEBUG("push item\n");
        ret = array_push(&a1, &temp);
        if(-1 == ret){
            __MDEBUG("push i=%d item='reject' ret=%d\n", i, ret);
            array_do_all(&a1, &print_item, NULL);
            printf("\n");
            break;
        }
        else{
            __MDEBUG("push i=%d item=(%d,%d) ret=%d\n", i, temp.first, temp.second, ret);
            array_do_all(&a1, &print_item, NULL);
            printf("\n");
        }
        temp.first=i*2;
        temp.second=i*3;
        ret = array_push(&a2, &temp);
        if(-1 == ret){
            __MDEBUG("push i=%d item='reject' ret=%d\n", i, ret);
            array_do_all(&a2, &print_item, NULL);
            printf("\n");
            break;
        }
        else{
            __MDEBUG("push i=%d item=(%d,%d) ret=%d\n", i, temp.first, temp.second, ret);
            array_do_all(&a2, &print_item, NULL);
            printf("\n");
        }
        printf("\n");
    }

    int tmp = 2;
    __MDEBUG("find item that first=%d\n", tmp);
    array_do_all(&a1, &find_item, &tmp);
    array_do_all(&a2, &find_item, &tmp);

    printf("\n");
    __MDEBUG("free a\n");
    array_free(&a1);
    array_free(&a2);
    return 0;
}
