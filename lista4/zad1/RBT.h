#ifndef RBT_H_   /* Include guard */
#define RBT_H_

typedef struct RBTNode{
    struct RBTNode* p;
    struct RBTNode* l;
    struct RBTNode* r;
    char* val;
    //0 - black, 1 - red
    short color;
} RBTNode;

typedef struct RBT{
    RBTNode* root;
    RBTNode* nil;
    //data[0] - insertions, data[1] - deletions, data[2] - finds
    int data[3];
    int maxSize;
    int size;
} RBT;



RBTNode* newRBTNode(char val[], RBTNode* p);

RBT* newRBT();

void RBTLeftRotate(RBT* tree, RBTNode* node);
void RBTRightRotate(RBT* tree, RBTNode* node);

void RBTRepairInsertion(RBT* tree, RBTNode* node);
void RBTNodeInsert(RBT* tree, RBTNode* node, char val[]);
void RBTInsert(RBT* tree, char val[]);

void RBTInOrderWalk(RBT* tree);

void RBTLoad(RBT* tree, char* filename);

RBTNode* RBTNodeSearch(RBT* tree, RBTNode* node, char* val);
RBTNode* RBTSearch(RBT* tree, char* val);

RBTNode* RBTNodeMin(RBT* tree, RBTNode* node);
RBTNode* RBTMin(RBT* tree);

RBTNode* RBTNodeMax(RBT* tree, RBTNode* node);
RBTNode* RBTMax(RBT* tree);

RBTNode* RBTSuccessor(RBT* tree, char* val);

void RBTNodeDelete(RBT* tree, RBTNode* node);
int RBTDelete(RBT* tree, char* val);


#endif // RBT_H_