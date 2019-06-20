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

void queuePUSH(queue *queue, vertex* v, double prio){
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
  queue->T[i].v = v;
}

int queueIsEmpty(queue* queue){
  if(queue->used == 0) return 1;
  else return 0;
}

void queuePrint(queue* queue){
  if(queue->used > 0) printf("(%i, %f)", queue->T[0].v->name, queue->T[0].prio);
  for(int i =  1; i < queue->used; i++){
    printf(", (%i, %f)", queue->T[i].v->name, queue->T[i].prio);
  }
  printf("\n");
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

void queueChangePriority(queue* queue, vertex* v){
    for (int i = 0; i < queue->used; i++){
        if (queue->T[i].v == v){
            queue->T[i].prio = v->dist;
            break;
        }
    }
    queueHeap(queue);
}

void queuePOP(queue* queue){
  int i, j;
  double p;
  vertex* v;

  if (queue->used-- != 0){
    p = queue->T[queue->used].prio;
    v = queue->T[queue->used].v;

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
  queue->T[i].v = v;
  }
}