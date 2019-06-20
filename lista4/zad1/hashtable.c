#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "linkedlist.h"
#include "RBT.h"
#include "functions.h"

HASHTABLE* newHASHTABLE(int m, int type){
    HASHTABLE* tab = malloc(sizeof(HASHTABLE));
    tab->m = m;
    tab->type = type;
    if (type == 0){
        tab->table = malloc(sizeof(list)*m);
        for (int i = 0; i < m; i++){
            tab->table[i] = createList();
        }
    } else {
        tab->table = malloc(sizeof(RBT)*m);
        for (int i = 0; i < m; i++){
            tab->table[i] = newRBT();
        }
    }
    tab->size = 0;
    tab->maxSize = 0;
    tab->data[0] = 0;
    tab->data[1] = 0;
    tab->data[2] = 0;
    return tab;
}

int HASHMake(char* val){
    int hash = 0;
    for(int i = 0; i < strlen(val); ++i){
        hash += val[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return abs(hash);
}

void HASHInsert(HASHTABLE* tab, char* val){
    void* new = tab->table[HASHMake(val)%tab->m];
    if (tab->type == 0){
        addElement((list*)new, val);
    } else {
        RBTInsert((RBT*)new, val);
    }
    tab->size++;
    tab->data[0]++;
    if (tab->size > tab->maxSize) tab->maxSize = tab->size;
}

void HASHLoad(HASHTABLE* tab, char* filename){
    char* buffer = getWords(filename);
    char* token = strsep(&buffer, " ,-;:.*\t\b\n");
    while (token) {
        if (strcmp(token, "")!=0){
            HASHInsert(tab, token);
        }
        token = strsep(&buffer, " ,-;:.*\t\b\n");
    }
}

void HASHDelete(HASHTABLE* tab, char* val){
    long hash = HASHMake(val);
    void* new = tab->table[hash%tab->m];
    if (tab->type == 0){
        tab->size-=deleteElement((list*)new, val);
    } else {
        tab->size-=RBTDelete((RBT*)new, val);
    }
    tab->data[1]++;
}

char* HASHFind(HASHTABLE* tab, char* val){
    long hash = HASHMake(val);
    void* new = tab->table[hash%tab->m];
    if (tab->type == 0){
        findElement((list*)new, val);
    } else {
        RBTSearch((RBT*)new, val);
    }
    tab->data[2]++;
}

void HASHPrint(HASHTABLE* tab){
    for (int i = 0; i< tab->m; i++){
        if (tab->type == 0){
        list* struc = (list*) tab->table[i];
        listElement* temp = struc->start; 
        printf("Bucket %i: ", i);
        while (temp){
            printf("%s, ", temp->val);
            temp = temp->next;
        }
        printf("\n");
        } else {
            RBT* struc = (RBT*) tab->table[i];
            printf("Bucket %i: ", i);
            RBTInOrderWalk(struc);
        }
    }
}