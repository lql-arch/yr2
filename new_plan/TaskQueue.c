#include <pthread.h>
#include"TaskQueue.h"

pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

SPSCQueue *SPSCQueueInit(int threadNumber) // creat
{
    int err;
    SPSCQueue *pool;
    pool = (SPSCQueue*)malloc(sizeof(SPSCQueue));
    pool->first = NULL;
    pool->last = NULL;

    if((err = pthread_rwlock_init(&pool->lock,NULL)) != 0)
    {
        exit(-1);
    }
    return 0;
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
    MPM *t;
    t = (MPM*)malloc(sizeof(MPM));
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

void *MPMCQueuePop(MPMCQueue *pool)
{
    MPM* t;
    t = pool->first;

    pool->first = pool->first->next;
    pool->first->prve = NULL;
    free(t->str);
    free(t);
}

void MPMCQueueDestory(MPMCQueue *mp)
{
    while(mp->first != NULL)
    {
        mp->first = mp->first->next;
        free(mp->first->prve->str);
        free(mp->first->prve);
    }
    free(mp);
}

int main()
{
    


    return 0;
}