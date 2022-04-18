#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"TaskQueue.h"


SPSCQueue *SPSCQueueInit(int threadNumber) // creat
{
    SPSCQueue *pool;
    pool = (SPSCQueue*)malloc(sizeof(SPSCQueue));
    pool->first = NULL;
    pool->last = NULL;
    
}

void SPSCQueuePush(SPSCQueue *pool, void *s) // end join
{
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

}

void *SPSCQueuePop(SPSCQueue *pool) //first delete
{
    SPS* t;
    t = pool->first;

    pool->first = pool->first->next;
    pool->first->prve = NULL;
    free(t->str);
    free(t);

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



MPMCQueue *MPMCQueueInit(int threadNumber)
{
    MPMCQueue *pool;
    pool = (MPMCQueue*)malloc(sizeof(MPMCQueue));
    pool->first = NULL;
    pool->last = NULL;
}

void MPMCQueuePush(MPMCQueue *pool, void *s)
{
    
}

void *MPMCQueuePop(MPMCQueue *pool)
{

}

void MPMCQueueDestory(MPMCQueue *mp)
{

}