#ifndef STATICTHREADPOOL_H
#define STATICTHREADPOOL_H

#include "UnboundedBlockingMPMCQueue.h"

#define THREAD_NUM 16

typedef void (*TaskFunction)(void* arg);

typedef struct {
    pthread_t workers_[THREAD_NUM];
    UnboundedBlockngMPMCQueue tasks_;
    TaskFunction task_function;
} ThreadPool;

void threadpool_init(ThreadPool* tp , TaskFunction func);

void threadpool_submit(ThreadPool* tp, void *task);

void threadpool_join(ThreadPool* tp);

void* WorkerRoutine(void* arg);

#endif