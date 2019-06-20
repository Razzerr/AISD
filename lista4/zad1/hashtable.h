#ifndef HASHTABLE_H_   /* Include guard */
#define HASHTABLE_H_

typedef struct HASHTABLENode{
    void* dataStruct;
} HASHTABLENode;

typedef struct HASHTABLE{
    int m;
    //0 - list, 1 - RBT
    int type;
    //data[0] - insertions, data[1] - deletions, data[2] - finds
    int data[3];
    int maxSize;
    int size;
    void** table;
} HASHTABLE;


HASHTABLENode* newHASHTABLENode(int type);

HASHTABLE* newHASHTABLE(int m, int type);

int HASHMake(char* val);

void HASHInsert(HASHTABLE* tab, char* val);

void HASHLoad(HASHTABLE* tab, char* filename);

void HASHDelete(HASHTABLE* tab, char* val);

char* HASHFind(HASHTABLE* tab, char* val);

void HASHPrint(HASHTABLE* tab);

#endif // HASHTABLE_H_