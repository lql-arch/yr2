#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include"TaskQueue.h"

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

SPSCQueue *SPSCQueueInit(int alloc) // creat
{
    //int err;
    SPSCQueue *pool;
    pool->alloc = alloc ;
    pool->size = 0;
    pool = (SPSCQueue*)malloc(sizeof(SPSCQueue));
    pool->first = NULL;
    pool->last = NULL;

    // if((err = pthread_rwlock_init(&pool->lock,NULL)) != 0)
    // {
    //     exit(-1);
    // }
    return pool;
}

void SPSCQueuePush(SPSCQueue *pool, void *s) // end join
{
    if(pool -> size == pool -> alloc)
    {
        fprintf(stderr,"error: over alloc.\n");
        return ;
    }

    SPS *t;
    t = (SPS*)malloc(sizeof(SPS));
    t->str = (char*)malloc(strlen((char*)s)+1);
    strcpy(t->str,(char*)s);
    t->str[strlen((char*)s)] = '\0';

    t->prve = pool->last;
    t->next = NULL;
    if(pool->last != NULL)
    {
        pool->last->next = t;
    }else{
        pool->first = t;
    }
    pool->last = t;

    pool->size += 1;

}

void *SPSCQueuePop(SPSCQueue *pool) //first delete
{
    if(pool->size == 0){
        fprintf(stderr,"error: no things.\n");
        return NULL;
    }
    char num[strlen(pool->first->str)+1];
    strcpy(num,pool->first->str);

    SPS* t;
    t = pool->first;

    pool->first = pool->first->next;
    pool->first->prve = NULL;
    free(t->str);
    free(t);

    pool->size -= 1;

    return ;
}

void SPSCQueueDestory(SPSCQueue *sp) //destory
{

    while(sp->first != NULL)
    {
        sp->first = sp->first->next;
        free(sp->first->prve->str);
        free(sp->first->prve);
    }
    free(sp);

}

void PrintQueue(SPSCQueue * sp){
    SPS * t = sp->first;
    while(t != NULL){
        printf("%s\n",t->str);
        t = t->next;
    }
}


int main()
{
    SPSCQueue* t = SPSCQueueInit(3);
    SPSCQueuePush(t,"114514");
    PrintQueue(t);


    return 0;
}