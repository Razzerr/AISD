#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct qelement{
  int prio, val;
} qelement;

typedef struct queue{
  qelement *T; // kopiec dynamiczny
  int used;        // liczba elementów
  int size;
} queue;

queue *NEWQueue(){
  queue *temp = malloc(sizeof(queue));
  temp->used = 0;
  temp->size = 32;
  temp->T = malloc(sizeof(qelement) * temp->size);
  return temp;
}

void queuePUSH(queue *queue, int v, int prio){
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
  queue->T[i].val = v;
}

void queueIsEmpty(queue* queue){
  if(queue->used == 0) printf("1\n");
  else printf("0\n");
}

void queueTOP(queue* queue){
  if(queue->used > 0) printf("%i\n", queue->T[0].val);
  else printf("\n");
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

void queuePriority(queue* queue, int val, int prio){
  for(int i = 0; i < queue->used; i++){
    if (queue->T[i].val == val && queue->T[i].prio < prio){
      queue->T[i].prio = prio;
    }
  }
  if(queue->used>0){
    queueHeap(queue);
  }
}

void queuePrint(queue* queue){
  if(queue->used > 0) printf("(%i, %i)", queue->T[0].val, queue->T[0].prio);
  for(int i =  1; i < queue->used; i++){
    printf(", (%i, %i)", queue->T[i].val, queue->T[i].prio);
  }
  printf("\n");
}

void queuePOP(queue* queue){
  int i, j, v, p;
  queueTOP(queue);

  if (queue->used-- != 0){
    p = queue->T[queue->used].prio;
    v = queue->T[queue->used].val;

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
  queue->T[i].val = v;
  } else (queue->used++);
}

int main(){
    queue* queue = NEWQueue();
    fseek(stdin, 0, SEEK_END);
    int numbytes = ftell(stdin);
    fseek(stdin, 0, SEEK_SET);

    char* buffer = malloc(numbytes*sizeof(char));
    fread(buffer, sizeof(char), numbytes+1, stdin);

    char* token = strsep(&buffer, " \n");
    token = strsep(&buffer, " \n");
    while(token){
        if(strcmp(token, "insert") == 0){
            token = strsep(&buffer, " \n");
            char* val = token;
            token = strsep(&buffer, " \n");
            char* prio = token;
            queuePUSH(queue, strtoumax(val, NULL, 10), strtoumax(prio, NULL, 10));
        } else if(strcmp(token, "empty") == 0){
          queueIsEmpty(queue);
        } else if(strcmp(token, "top") == 0){
          queueTOP(queue);
        } else if(strcmp(token, "pop") == 0){
          queuePOP(queue);
        } else if(strcmp(token, "priority") == 0){
          token = strsep(&buffer, " \n");
            char* val = token;
            token = strsep(&buffer, " \n");
            char* prio = token;
            queuePriority(queue, strtoumax(val, NULL, 10), strtoumax(prio, NULL, 10));
        } else if(strcmp(token, "print") == 0){
            queuePrint(queue);
        }
        token = strsep(&buffer, " \n");
    }
}