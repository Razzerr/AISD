#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BST.h"
#include "RBT.h"
#include "hashtable.h"

int* useBST(){
    BST* temp = newBST();

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
            if (token) BSTInsert(temp, token);
        } else if (strcmp(token, "load") == 0){
            token = strsep(&buffer, " \n");
            if (token) BSTLoad(temp, token);
        } else if (strcmp(token, "delete") == 0){
            token = strsep(&buffer, " \n");
            if (token) BSTDelete(temp, token);
        } else if (strcmp(token, "find") == 0){
            token = strsep(&buffer, " \n");
            if (token) BSTSearch(temp, token);
        } else if (strcmp(token, "min") == 0){
            BSTMin(temp);
        } else if (strcmp(token, "max") == 0){
            BSTMax(temp);
        } else if (strcmp(token, "successor") == 0){
            token = strsep(&buffer, " \n");
            if (token) BSTSuccessor(temp, token);
        } else if (strcmp(token, "inorder") == 0){
            BSTInOrderWalk(temp);
        }
        token = strsep(&buffer, " \n");
    } 
    int* result = malloc(sizeof(int)*5);
    result[0] = temp->data[0];
    result[1] = temp->data[1];
    result[2] = temp->data[2];
    result[3] = temp->maxSize;
    result[4] = temp->size;
    return result;
}

int* useRBT(){
    RBT* temp = newRBT();

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
            if (token) RBTInsert(temp, token);
        } else if (strcmp(token, "load") == 0){
            token = strsep(&buffer, " \n");
            if (token) RBTLoad(temp, token);
        } else if (strcmp(token, "delete") == 0){
            token = strsep(&buffer, " \n");
            if (token) RBTDelete(temp, token);
        } else if (strcmp(token, "find") == 0){
            token = strsep(&buffer, " \n");
            if (token) RBTSearch(temp, token);
        } else if (strcmp(token, "min") == 0){
            RBTMin(temp);
        } else if (strcmp(token, "max") == 0){
            RBTMax(temp);
        } else if (strcmp(token, "successor") == 0){
            token = strsep(&buffer, " \n");
            if (token) RBTSuccessor(temp, token);
        } else if (strcmp(token, "inorder") == 0){
            RBTInOrderWalk(temp);
        }
        token = strsep(&buffer, " \n");
    } 
    int* result = malloc(sizeof(int)*5);
    result[0] = temp->data[0];
    result[1] = temp->data[1];
    result[2] = temp->data[2];
    result[3] = temp->maxSize;
    result[4] = temp->size;
    return result;
}

int* useHASH(){
    fseek(stdin, 0, SEEK_END);
    int numbytes = ftell(stdin);
    fseek(stdin, 0, SEEK_SET);

    char* buffer = malloc(numbytes*sizeof(char));
    fread(buffer, sizeof(char), numbytes+1, stdin);
    int m = 127;
    HASHTABLE* temp = newHASHTABLE(m, (numbytes/(5*m) > 100)?1:0);

    char* token = strsep(&buffer, " \n");
    token = strsep(&buffer, " \n");
    while(token){
        if(strcmp(token, "insert") == 0){
            token = strsep(&buffer, " \n");
            if (token) HASHInsert(temp, token);
        } else if (strcmp(token, "load") == 0){
            token = strsep(&buffer, " \n");
            if (token) HASHLoad(temp, token);
        } else if (strcmp(token, "delete") == 0){
            token = strsep(&buffer, " \n");
            if (token) HASHDelete(temp, token);
        } else if (strcmp(token, "find") == 0){
            token = strsep(&buffer, " \n");
            if (token) HASHFind(temp, token);
        } else if (strcmp(token, "min") == 0){
            printf("\n");
        } else if (strcmp(token, "max") == 0){
            printf("\n");
        } else if (strcmp(token, "successor") == 0){
            printf("\n");
        } else if (strcmp(token, "inorder") == 0){
            printf("\n");
        }
        token = strsep(&buffer, " \n");
    } 
    int* result = malloc(sizeof(int)*5);
    result[0] = temp->data[0];
    result[1] = temp->data[1];
    result[2] = temp->data[2];
    result[3] = temp->maxSize;
    result[4] = temp->size;
    return result;
}

void main(int argc, char *argv[]) {
    //type: 0 - BST, 1 - RBT, 2 - HASHMAP
    int type = 0;
    //"menu" for switching arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--type") == 0 && argc > i + 1) {
            if (strcmp(argv[i + 1], "bst") == 0) type = 0;
            else if (strcmp(argv[i + 1], "rbt") == 0) type = 1;
            else if (strcmp(argv[i + 1], "hmap") == 0) type = 2; 
            else {
                fprintf(stderr, "Wrong '--type' argument given: %s", argv[i + 1]);
                return;
            }
        }
    }
    int* data;
    clock_t start, end;
    switch(type){
        case 0:
            start = clock();
            data = useBST();
            end = clock();
            fprintf(stderr, "Time: %f\nInserts: %i\nDeletions: %i\nFinds: %i\nMax elements: %i\nFinish elements: %i", 
                ((double) (end - start)) / CLOCKS_PER_SEC, data[0], data[1], data[2], data[3], data[4]);
            break;
        case 1:
            start = clock();
            data = useRBT();
            end = clock();
            fprintf(stderr, "Time: %f\nInserts: %i\nDeletions: %i\nFinds: %i\nMax elements: %i\nFinish elements: %i", 
                ((double) (end - start)) / CLOCKS_PER_SEC, data[0], data[1], data[2], data[3], data[4]);
            break;
        case 2:
            start = clock();
            data = useHASH();
            end = clock();
            fprintf(stderr, "Time: %f\nInserts: %i\nDeletions: %i\nFinds: %i\nMax elements: %i\nFinish elements: %i", 
                ((double) (end - start)) / CLOCKS_PER_SEC, data[0], data[1], data[2], data[3], data[4]);
            break;
    }
}