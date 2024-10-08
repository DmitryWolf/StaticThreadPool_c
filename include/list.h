#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t size;
} List;

void list_init(List *list);

void list_push_back(List *list, void *data);

void *list_pop_front(List *list);

size_t list_size(List *list);

void list_clear(List *list);

#endif