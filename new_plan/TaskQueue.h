#include <unistd.h>
#include <pthread.h>

#define MAXSIZE 100

// typedef struct data_control {
//     pthread_mutex_t mutex;
//     pthread_cond_t cond;
//     int active;
// } data_control;

typedef struct SPS{
    char *str;
    struct SPS *next,*prve;
}SPS;

typedef struct SPSCQueue{
    struct SPS *last,*first;
}SPSCQueue;

SPSCQueue *SPSCQueueInit(int threadNumber);
void SPSCQueuePush(SPSCQueue *pool, void *s);
void *SPSCQueuePop(SPSCQueue *pool);
void SPSCQueueDestory(SPSCQueue *sps);


struct MPMCQueue {
    struct MPM *last,*first;
} typedef MPMCQueue;

typedef struct MPM{
    char *str;
    struct MPM *next,*prve;
}MPM;

MPMCQueue *MPMCQueueInit(int threadNumber);
void MPMCQueuePush(MPMCQueue *pool, void *s);
void *MPMCQueuePop(MPMCQueue *pool);
void MPMCQueueDestory(MPMCQueue *mpm);