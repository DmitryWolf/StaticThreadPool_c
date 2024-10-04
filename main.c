#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StaticThreadPool.h"

void testlist(){
    List list;
    list_init(&list);
    int v = 1;
    list_push_back(&list, &v);
    void* pfv = list_pop_front(&list);
    printf("%d\n", *(int *)pfv);
    list_clear(&list);
}

void testMPMQ(){
    UnboundedBlockngMPMCQueue queue;
    MPMCQueue_init(&queue);
    int v = 1;
    MPMCQueue_put(&queue, &v);
    void *tv = MPMCQueue_take(&queue);
    printf("%d\n", *(int *)tv);
    MPMCQueue_clear(&queue);
}

typedef struct {
    int a;
    int b;
} Task;

void mysum(void* arg) {
    Task* t = (Task*)arg;
    int result = t->a + t->b;
    printf("Sum: %d\n", result);
    free(t);
}

void testTP(){
    ThreadPool tp;
    threadpool_init(&tp, mysum);
    for (int i = 0; i < 100000; i++){
        Task *t = malloc(sizeof(Task));
        t->a = rand() % 100;
        t->b = rand() % 100;
        threadpool_submit(&tp, t);
    }
    threadpool_join(&tp);
}



int main() {
    testlist();
    testMPMQ();
    testTP();
    return 0;
}
