#ifndef PRIORITYQUEUE_H_   /* Include guard */
#define PRIORITYQUEUE_H_
#include "graph.h"

typedef struct qelement{
    double prio;
    vertex* v;
} qelement;

typedef struct queue{
  qelement *T; // kopiec dynamiczny
  int used;        // liczba elementów
  int size;
} queue;

queue *NEWQueue();

void queuePUSH(queue *queue, vertex* v, double prio);

int queueIsEmpty(queue* queue);

void queuePrint(queue* queue);

void queueChangePriority(queue* queue, vertex* v);

void queuePOP(queue* queue);

void queueHeapify(queue* queue, int i);

void queueHeap(queue* queue);


#endif // PRIORITYQUEUE_H_