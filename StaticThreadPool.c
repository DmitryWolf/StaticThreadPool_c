#include "StaticThreadPool.h"

void threadpool_init(ThreadPool* tp , TaskFunction func) {
    MPMCQueue_init(&tp->tasks_);
    tp->task_function = func;
    for (int i = 0; i < THREAD_NUM; ++i) {
        if (pthread_create(&tp->workers_[i], NULL, WorkerRoutine, (void*)tp) != 0) {
            perror("Failed to create the thread");
        }
    }
}


void threadpool_submit(ThreadPool* tp, void *task) {
    MPMCQueue_put(&tp->tasks_, task);
}

void threadpool_join(ThreadPool* tp) {
    for (int i = 0; i < THREAD_NUM; ++i) {
        MPMCQueue_put(&tp->tasks_, NULL);
    }
    for (int i = 0; i < THREAD_NUM; ++i) {
        if (pthread_join(tp->workers_[i], NULL) != 0) {
            perror("Failed to join the thread");
        }
    }
    MPMCQueue_clear(&tp->tasks_);
}

void* WorkerRoutine(void* arg) {
    ThreadPool* tp = (ThreadPool*)arg;
    while (1) {
        void* task = MPMCQueue_take(&tp->tasks_);
        if (!task) {
            break;
        }
        tp->task_function(task);

    }
    return NULL;
}