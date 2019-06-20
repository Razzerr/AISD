#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
list *createList() {
    list *new = malloc(sizeof(list));
    new->start = NULL;
    new->count = 0;
    return new;
}

listElement *createElement(char* input) {
    listElement *new = malloc(sizeof(listElement));
    new->next = NULL;
    new->val = input;
    return new;
}

void addElement(list *list, char* input) {
    listElement *n = createElement(input);
    if (list->start == NULL) {
        list->start = n;
    } else {
        n->next = list->start;
        list->start = n;
    }
    list->count++;
}

int deleteElement(list *list, char* elem) {
    if (list->start == NULL) {
        return 0;
    }
    listElement* temp = list->start;
    listElement* prev = NULL;
    while(temp){
        if (strcmp(temp->val, elem)==0) {
            if (temp->next != NULL){
                if(prev != NULL){
                    prev->next = temp->next;
                } else {
                    list->start = temp->next;
                }
            }
            if (list->start == temp){
                list->start = NULL;
            }
            free(temp);
            if (prev!=NULL) prev->next = NULL;
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}

void findElement(list *list, char* elem) {
    listElement* temp = list->start;
    while(temp){
        if (strcmp(temp->val, elem) == 0){
            printf("%i\n", 1);
            return;
        }
        temp = temp->next;
    }
    printf("%i\n", 0);
}