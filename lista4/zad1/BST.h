#ifndef BST_H_   /* Include guard */
#define BST_H_

typedef struct BSTNode{
    struct BSTNode* p;
    struct BSTNode* l;
    struct BSTNode* r;
    char* val;
} BSTNode;

typedef struct BST{
    BSTNode* root;
    //data[0] - insertions, data[1] - deletions, data[2] - finds
    int data[3];
    int maxSize;
    int size;
} BST;



BSTNode* newBSTNode(char val[], BSTNode* p);

BST* newBST();

int BSTNodeInsert(BSTNode* node, char val[]);
void BSTInsert(BST* tree, char val[]);

void BSTInOrderWalk(BST* tree);

void BSTLoad(BST* tree, char* filename);

BSTNode* BSTNodeSearch(BSTNode* node, char* val);
BSTNode* BSTSearch(BST* tree, char* val);

BSTNode* BSTNodeMin(BSTNode* node);
BSTNode* BSTMin(BST* tree);

BSTNode* BSTNodeMax(BSTNode* node);
BSTNode* BSTMax(BST* tree);

BSTNode* BSTSuccessor(BST* tree, char* val);

int BSTNodeDelete(BSTNode* node);
void BSTDelete(BST* tree, char* val);


#endif // BST_H_