#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct element {
    struct element *next;
    char val;
} element;

typedef struct list {
    element *start;
    unsigned count;
} list;

list *createList() {
    list *new;
    new = (list *) malloc(sizeof(list));
    new->start = NULL;
    new->count = 0;
    return new;
}

element *createElement(char input) {
    element *new;
    new = (element *) malloc(sizeof(element));
    new->next = NULL;
    new->val = input;
    return new;
}

void addElementBack(list *list, char input) {
    element *temp =  list->start;
    element *new = createElement(input);
    if (list->start!=NULL){
        while (temp->next!=NULL) {
            temp = temp->next;
        }
        temp->next = new;
    }
    else {
        list->start = new;
    }
    list->count++;
}

void deleteElementBack(list *list) {
    element *temp = list->start;
    if (list->start == NULL) {
        return;
    }  else if (temp->next==NULL){
        free(temp);
        list->start = NULL;
        list->count--;
    } else {
        while (temp->next->next!=NULL) {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
        list->count--;
    }
}

void showList(list *list) {
    element *temp = list->start;
    printf("Start -> ");
    while(temp!=NULL){
        printf("%c -> ", temp->val);
        temp = temp->next;
    }
    printf("End");
}

void showListAddresses(list *list) {
    element *temp = list->start;
    printf("Start -> ");
    while(temp!=NULL){
        printf("%p -> ", (void *)&(temp->val));
        temp = temp->next;
    }
    printf("End");
}

char findElement(list *list, int index) {
    int count = 0;
    element *temp = list->start;
    if (index>=0 && index<list->count){
        while (count != index){
            temp = temp->next;
            count++;
        }
    } else {
        fprintf(stderr, "!> Index out of range");
        return '\0';
    }
    return temp->val;
}

list *deepCopy(list *inputList){
    list *tempList = createList();
    element *tempElement = inputList->start;
    while (tempElement){
        addElementBack(tempList, tempElement->val);
        tempElement = tempElement->next;
    }
    return tempList;
}

list *megre(list *listA, list *listB) {
    list *merged = createList(),  *list1 = deepCopy(listA), *list2 = deepCopy(listB);
    element *tempelement = list1->start;
    while(tempelement->next){
        tempelement = tempelement->next;
    }
    tempelement->next = list2->start;
    merged->start = list1->start;
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