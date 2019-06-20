#ifndef LINKEDLIST_H_   /* Include guard */
#define LINKEDLIST_H_

typedef struct listElement {
    struct listElement *next;
    char* val;
} listElement;

typedef struct list {
    listElement *start;
    long count;
} list;

list *createList();

listElement *createElement(char* input);

void addElement(list *list, char* input);

int deleteElement(list *list, char* elem);

void findElement(list *list, char* elem) ;


#endif // LINKEDLIST_H_