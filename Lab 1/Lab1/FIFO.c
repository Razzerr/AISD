#include <stdio.h>
#include <stdlib.h>

typedef struct FIFO{
    char queue[1024];
    char* head;
    char* tail;
} FIFO;

FIFO *createFIFO() {
    FIFO *new = (FIFO *)malloc(sizeof(FIFO));
    for (int i = 0; i< sizeof(new->queue)/ sizeof(char); i++){
        new->queue[i] = '\0';
    }
    new->head = new->queue + sizeof(new->queue);
    new->tail = new->queue;
}

void enqueue(FIFO *queue, char a) {
    if ((queue->head!=queue->queue+sizeof(queue->queue) && *(queue->head + sizeof(char)) != '\0')
        || (queue->head==queue->queue+sizeof(queue->queue) && *(queue->queue) != '\0')
        || a == '\0') {
        fprintf(stderr, "!> [Error] Can't enqueue an item! Reason: queue is full or empty char passed.\n");
        return;
    }else if (queue->head == queue->queue + sizeof(queue->queue)) {
        queue->head = queue->queue;
        *queue->head = a;
    } else {
        queue->head += sizeof(char);
        *queue->head = a;
    }
}

char *dequeue(FIFO *queue) {
    char *temp = '\0';
    if (*(queue->tail) == '\0') {
        fprintf(stderr, "!> [Error] Can't dequeue an item! Reason: queue is empty!\n");
        return '\0';
    }else if (queue->tail == queue->queue + sizeof(queue->queue)) {
        temp = queue->tail;
        queue->tail = '\0';
        queue->tail = queue->queue;
    } else {
        temp = queue->tail;
        *(queue->tail) = '\0';
        queue->tail += sizeof(char);
    }
    return temp;
}

char view_elem(FIFO *queue, int index) {
    if (index < sizeof(queue->queue)/ sizeof(char) && index >= 0) {
        return queue->queue[index];
    } else {
        printf("Index out of range!");
        return '\0';
    }
}

void showQueue(FIFO *queue){
    for (int i = 0; i < sizeof(queue->queue)/ sizeof(char); i++){
        printf( "%c -> ", queue->queue[i]);
    }
}

int main() {
    FIFO *fifo = createFIFO();

    //enqueueing 128 elements
    printf("\nEnqueueing 128 elements:\n");
    for(int i = 0; i<128; i++){
        enqueue(fifo, 'a');
    }

    //showing queue
    showQueue(fifo);

    printf("\nDequeueing 64 elements:\n");

    //dequeueing 64 elements
    char *temp = '\0';
    for (int i = 0; i<64; i++) {
        temp = dequeue(fifo);
    }
    showQueue(fifo);
}