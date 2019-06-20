#include <stdio.h>
#include <stdlib.h>
#include <sysinfoapi.h>
#include <sys/time.h>

typedef struct element {
    struct element *next, *prev;
    char val;
} element;

typedef struct list {
    element *start, *end;
    unsigned count;
} list;

list *createList() {
    list *new;
    new = (list *) malloc(sizeof(list));
    new->start = NULL;
    new->count = 0;
    new->end = NULL;
    return new;
}

element *createElement(char input) {
    element *new;
    new = (element *) malloc(sizeof(element));
    new->next = NULL;
    new->val = input;
    new->prev = NULL;
    return new;
}

void addElementBack(list *list, char input) {
    element *n = createElement(input);
    if (list->start == NULL) {
        list->start = n;
        list->end = n;
        list->start->prev = list->end;
        list->start->next = list->end;
    } else {
        n->prev = list->end;
        n->next = list->start;
        list->start->prev = n;
        list->end->next = n;
        list->end = n;
    }
    list->count++;
}

void deleteElementBack(list *list) {
    if (list->start == NULL) {
        return;
    } else if (list->start->prev == list->start) {
        list->start = NULL;
        free(list->end);
        list->end = NULL;
        list->count--;
    } else {
        element *temp = list->end;
        list->end = list->end->prev;
        list->end->next = list->start;
        list->start->prev = list->end;
        free(temp);
        temp = NULL;
        list->count--;
    }
}

void showList(list *list) {
    element *temp = list->start;

    int counter = 0;
    if (list->count != 0) {
        while (counter < list->count) {
            printf("<-prev- %c -next->", temp->val);
            temp = temp->next;
            counter++;
        }
    }
}

void showListAddresses(list *list) {
    element *temp = list->start;

    int counter = 0;
    if (list->count != 0) {
        while (counter < list->count) {
            printf("<-prev- %p -next->", (void*)&(temp->val));
            temp = temp->next;
            counter++;
        }
    }
}

char findElement(list *list, int index) {
    int count = 0;
    element *temp;
    switch (list->count) {
        case 0:
            fprintf(stderr, "!> List is empty!");
            return '\0';
        default:
            if (index > list->count-1) {
                fprintf(stderr, "!> Index out of bounds.");
                return '\0';
            } else if (index < (int) (list->count / 2)) {
                temp = list->start;
                while (count != index) {
                    temp = list->start->next;
                    count++;
                }
            } else {
                temp = list->end;
                while (count != list->count - (index + 1)) {
                    temp = list->end->prev;
                    count++;
                }
            }

            break;
    }
    return temp->val;
}

list *deepCopy(list *inputList){
    list *tempList = createList();
    element *tempElement = inputList->start;
    do {
        addElementBack(tempList, tempElement->val);
        tempElement = tempElement->next;
    } while(tempElement!=inputList->start);
    return tempList;
}

list *megre(list *listA, list *listB) {
    list *merged = createList(),  *list1 = deepCopy(listA), *list2 = deepCopy(listB);
    list1->end->next = list2->start;
    list1->start->prev = list2->end;
    list2->end->next = list1->start;
    list2->start->prev = list1->end;
    merged->start = list1->start;
    merged->end = list2->end;
    merged->count = list1->count + list2->count;
    return merged;
}

double getTimeElapsed(struct timeval end, struct timeval start) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.00;
}

int main(){
    list *list = createList(), *list1 = createList(), *list2 = createList(), *merged;
    time_t t;

    //Adding 1000 random elements to the list
    srand((unsigned) time(&t));
    for(int i = 0 ; i < 1000 ; i++ ) {
        char tempchar = (char)(97+(rand() % 25));
        addElementBack(list, tempchar);
    }
    printf("> 1000 elements added!\n");

    //Access time to a given element
    double tempdouble = 0;
    struct timeval tvalBefore, tvalAfter;

    gettimeofday(&tvalBefore, NULL);
    for (int j = 0; j<100000; j++) {
        findElement(list, 0);
    }
    gettimeofday(&tvalAfter, NULL);
    tempdouble = getTimeElapsed(tvalAfter, tvalBefore)/100000;
    printf("> Time elapsed to find 1st element: %g\n", tempdouble);

    tempdouble = 0;
    gettimeofday(&tvalBefore, NULL);
    for (int j = 0; j<100000; j++) {
        findElement(list, 499);
    }
    gettimeofday(&tvalAfter, NULL);
    tempdouble = getTimeElapsed(tvalAfter, tvalBefore)/100000;
    printf("> Time elapsed to find 500th element: %g\n", tempdouble);


    tempdouble = 0;
    gettimeofday(&tvalBefore, NULL);
    for (int j = 0; j<100000; j++) {
        findElement(list, 999);
    }
    gettimeofday(&tvalAfter, NULL);
    tempdouble = getTimeElapsed(tvalAfter, tvalBefore)/100000;
    printf("> Time elapsed to find 1000th element: %g\n", tempdouble);


    //Access time to a random element
    tempdouble = 0;
    for (int j = 0; j < 100000; j++) {
        int tempint = (rand() % 1000);
        gettimeofday(&tvalBefore, NULL);
        findElement(list, tempint);
        gettimeofday(&tvalAfter, NULL);
        tempdouble += getTimeElapsed(tvalAfter, tvalBefore);
    }
    tempdouble = tempdouble/ 100000;
    printf("> Time elapsed to find a random element: %g\n", tempdouble);


    //Merge
    char chars[4] = {'a', 'b', 'c', 'd'};
    addElementBack(list1, chars[0]);
    addElementBack(list1, chars[1]);
    addElementBack(list2, chars[2]);
    addElementBack(list2, chars[3]);
    merged = megre(list1, list2);

    printf("\n> List 1: ");
    showList(list1);

    printf("\n> List 1 <addresses>: ");
    showListAddresses(list1);

    printf("\n> List 2: ");
    showList(list2);

    printf("\n> List 2 <addresses>: ");
    showListAddresses(list2);

    printf("\n> Merged: ");
    showList(merged);

    printf("\n> Merged <addresses>: ");
    showListAddresses(merged);
    getchar();
}