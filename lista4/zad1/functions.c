
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

char* getWords(char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        fprintf(stderr, "File does not exist!");
        return NULL;
    }
    int numbytes;

    fseek(file, 0, SEEK_END);
    numbytes = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(numbytes*sizeof(char));
    fread(buffer, sizeof(char), numbytes+1, file);
    fclose(file);

    return buffer;
}