#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "priorityQueue.h"

queue *NEWQueue(){
  queue *temp = malloc(sizeof(queue));
  temp->used = 0;
  temp->size = 32;
  temp->T = malloc(sizeof(qelement) * temp->size);
  return temp;
}

void queuePUSH(queue *queue, edge* e, double prio){
  int i, j;

  i = queue->used++;
  j = (i - 1) / 2;

  if (queue->used == queue->size){
    queue->size *= 2;
    queue->T = realloc(queue->T, sizeof(qelement)*queue->size);
  }

  while (i > 0 && queue->T[j].prio > prio){
    queue->T[i] = queue->T[j];
    i = j;
    j = (i - 1) / 2;
  }

  queue->T[i].prio = prio;
  queue->T[i].e = e;
}

int queueIsEmpty(queue* queue){
  if(queue->used == 0) return 1;
  else return 0;
}

void queueHeapify (queue* queue, int i){
  int largest, N = queue->used;
  int left = 2*i + 1;
  int right = 2*i + 2;
  if(left < N && queue->T[left].prio < queue->T[i].prio)
        largest = left;
  else
        largest = i;
  if(right < N && queue->T[right].prio < queue->T[largest].prio)
      largest = right;
  if(largest != i){
    qelement temp = queue->T[i];
    queue->T[i] = queue->T[largest];
    queue->T[largest] = temp;
    queueHeapify (queue, largest);
  } 
}

void queueHeap (queue* queue){
    for(int i = queue->used/2 ; i >= 0 ; i-- ){
        queueHeapify(queue, i);
    }
}

void queuePrint(queue* queue){
  if(queue->used > 0) printf("(%i, %i, %f)", queue->T[0].e->u, queue->T[0].e->v, queue->T[0].prio);
  for(int i =  1; i < queue->used; i++){
    printf("(%i, %i, %f)", queue->T[i].e->u, queue->T[i].e->v, queue->T[i].prio);
  }
  printf("\n");
}

void queuePOP(queue* queue){
  int i, j;
  double p;
  edge* e;

  if (queue->used-- != 0){
    p = queue->T[queue->used].prio;
    e = queue->T[queue->used].e;

    i = 0;
    j = 1;

    while (j < queue->used){
      if (j + 1 < queue->used && queue->T[j + 1].prio < queue->T[j].prio)
      j++;
      if (p <= queue->T[j].prio)
      break;
      queue->T[i] = queue->T[j];
      i = j;
      j = 2 * j + 1;
    }

  queue->T[i].prio = p;
  queue->T[i].e = e;
  }
}