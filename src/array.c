#include "array.h"

int array_malloc(Array *a){
    a->ptr = NULL;
    a->ptr = malloc(a->item_size * a->item_num);
    if(NULL == a->ptr){
        __ADEBUG("%s(%p) alloc(%d items) failed\n", __func__, 
                a, a->item_num);
        return -1;
    }

    __ADEBUG("%s(%p) alloc(%d items) ok ptr(%p)\n", __func__, 
            a, a->item_num, a->ptr);
    return 0;
}

int array_realloc(Array *a){
    void *tmp_ptr;
    int tmp_num;
    int ret;

    tmp_ptr = a->ptr;
    tmp_num = a->item_num;
    a->item_num = a->item_num << _GROWTH_FACTOR;
    ret = array_malloc(a);
    if(-1 == ret){
        a->item_num = a->item_num >> _GROWTH_FACTOR;
        a->ptr = tmp_ptr;
        __ADEBUG("%s(%p) failed\n", __func__, a);
        return -1;
    }

    __ADEBUG("%s(%p) new_ptr=%p old_ptr=%p\n", __func__, a, a->ptr, tmp_ptr);
    memcpy(a->ptr, tmp_ptr, a->item_size * tmp_num);
    free(tmp_ptr);
    __ADEBUG("%s(%p) memcpy(%d items) done\n", __func__, a, tmp_num);
    return 0;
}

int array_init(Array *a, int item_size){
    a->item_size = item_size;
    a->item_num = _INITIAL_ITEM_NUM;
    a->index = 0;
    __ADEBUG("%s(%p) item_size=%d item_num=%d\n", __func__, 
            a, a->item_size, a->item_num);
    return array_malloc(a);
}

int array_size(Array *a){
   return a->index; 
}

void *array_get(Array *a, int index){
    if(index >= a->index){
        __ADEBUG("%s(%p) wrong index(%d)!\n", __func__, a, index);
        return NULL;
    }
    
    __ADEBUG("%s(%p) get index %d\n", __func__, a, index);
    return a->ptr + (a->item_size * index);
}

int array_push(Array *a, void *item){
    int ret;
    void *p;
    if(a->index == a->item_num){ //array_full
        ret = array_realloc(a);
        if(-1 == ret){
            __ADEBUG("%s(%p) full\n", __func__, a);
            return -1;
        }
    }
    p = a->ptr + (a->item_size * a->index);
    memcpy(p, item, a->item_size);
    a->index++;
    __ADEBUG("%s(%p) index=%d\n", __func__, a, a->index);
    return 0;
}

void array_free(Array *a){
    a->item_size = 0;
    free(a->ptr);
    a->ptr = NULL;
}

void array_do_all(Array *a, int (*fptr)(void *, void *), void *params){
    int index;
    int break_flag;
    void *p;

    __ADEBUG("%s(%p) \n", __func__, a);

    index = 0; /* index of first item is 1 */
    while(index < a->index){
        p = array_get(a, index);
        break_flag = (*fptr)(p, params);
        if(1 == break_flag) break;
        index++;
    }
}
