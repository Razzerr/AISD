#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "RBT.h"
#define BLACK 0
#define RED 1

RBTNode* newRBTNode(char val[], RBTNode* p){
    RBTNode* newRBTNode = malloc(sizeof(RBTNode));
    newRBTNode->p = p;
    newRBTNode->r = NULL;
    newRBTNode->l = NULL;
    newRBTNode->val = val;
    newRBTNode->color = RED;
    return newRBTNode;
}

RBT* newRBT(){
    RBT* newRBT = malloc(sizeof(RBT));
    newRBT->size = 0;
    newRBT->nil = newRBTNode(NULL, NULL);
    newRBT->nil->color = BLACK;
    newRBT->root = newRBT->nil;
    return newRBT;
}

void RBTLeftRotate(RBT* tree, RBTNode* node){
    RBTNode* y = node->r;
    node->r = y->l;
    if (y->l != tree->nil) y->l->p = node;
    y->p = node->p;
    if (node->p == tree->nil) tree->root = y;
    else{
        if (node == node->p->l) node->p->l = y;
        else node->p->r = y;
    }
    y->l = node;
    node->p = y;
}

void RBTRightRotate(RBT* tree, RBTNode* node){
    RBTNode* y = node->l;
    node->l = y->r;
    if (y->r != tree->nil) y->r->p = node;
    y->p = node->p;
    if (node->p == tree->nil) tree->root = y;
    else{
        if (node == node->p->r) node->p->r = y;
        else node->p->l = y;
    }
    y->r = node;
    node->p = y;
}

void RBTRepairInsertion(RBT* tree, RBTNode* node){
    while (node->p->color == RED){
        if (node->p == node->p->p->l){
            RBTNode* uncle = node->p->p->r;
            if (uncle->color == RED){
                node->p->color = BLACK;
                uncle->color = BLACK;
                node->p->p->color = RED;
                node = node->p->p;
            } else {
                if (node == node->p->r){
                    node = node->p;
                    RBTLeftRotate(tree, node);
                }
                node->p->color = BLACK;
                node->p->p->color = RED;
                RBTRightRotate(tree, node->p->p);
            }
        } else {
            RBTNode* uncle = node->p->p->l;
            if (uncle->color == RED){
                node->p->color = BLACK;
                uncle->color = BLACK;
                node->p->p->color = RED;
                node = node->p->p;
            } else {
                if (node == node->p->l){
                    node = node->p;
                    RBTRightRotate(tree, node);
                }
                node->p->color = BLACK;
                node->p->p->color = RED;
                RBTLeftRotate(tree, node->p->p);
            }
        }
    }
    tree->root->color = BLACK;
}

void RBTNodeInsert(RBT* tree, RBTNode* node, char* val){
    RBTNode* y = tree->nil;
    RBTNode* x = tree->root;
    while (x != tree->nil){
        y = x;
        if (strcmp(val, x->val) < 0) x = x->l;
        else x = x->r;
    }
    RBTNode* z = newRBTNode(val, y);
    if (strcmp(z->val, y->val) < 0) y->l = z;
    else y->r = z;
    z->l = tree->nil;
    z->r = tree->nil;
    RBTRepairInsertion(tree, z);
}

void RBTInsert(RBT* tree, char* val){
    if (tree->root == tree->nil){
        RBTNode* tempNode = newRBTNode(val, tree->nil);
        tempNode->color = BLACK;
        tempNode->l = tree->nil;
        tempNode->r = tree->nil;

        tree->root = tempNode;
    } else {
        RBTNodeInsert(tree, tree->root, val);
    }
    tree->size++;
    tree->data[0]++;
    if (tree->size > tree->maxSize) tree->maxSize = tree->size;
}

void RBTNodeInOrderWalk(RBT* tree, RBTNode* node){
    if (node != tree->nil){
        RBTNodeInOrderWalk(tree, node->l);
        printf("%s ", node->val);
        RBTNodeInOrderWalk(tree, node->r);
    }
}

void RBTInOrderWalk(RBT* tree){
    RBTNodeInOrderWalk(tree, tree->root);
    printf("\n");
}

void RBTLoad(RBT* tree, char* filename){
    char* buffer = getWords(filename);
    char* token = strsep(&buffer, " ,-;:.*\t\b\n");
    while (token) {
        if (strcmp(token, "")!=0){
            RBTInsert(tree, token);
        }
        token = strsep(&buffer, " ,-;:.*\t\b\n");
    }
}

RBTNode* RBTNodeSearch(RBT* tree, RBTNode* node, char* val){
    if (node == tree->nil || strcmp(val, node->val) == 0) return node;
    else if (strcmp(val, node->val) < 0) return RBTNodeSearch(tree, node->l, val);
    else return RBTNodeSearch(tree, node->r, val);
}

RBTNode* RBTSearch(RBT* tree, char* val){
    RBTNode* tempNode = RBTNodeSearch(tree, tree->root, val);
    if (tempNode == tree->nil) printf("0\n");
    else printf("1\n");
    tree->data[2]++;
    return tempNode;
}

RBTNode* RBTNodeMin(RBT* tree, RBTNode* node){
    if (node == tree->nil || node->l == tree->nil) return node;
    return RBTNodeMin(tree, node->l);
}

RBTNode* RBTMin(RBT* tree){
    RBTNode* temp = RBTNodeMin(tree, tree->root);
    if (temp == tree->nil) printf("\n");
    else printf("%s\n", temp->val);
    return temp;
}

RBTNode* RBTNodeMax(RBT* tree, RBTNode* node){
    if (node == tree->nil || node->r == tree->nil) return node;
    return RBTNodeMax(tree, node->r);
}

RBTNode* RBTMax(RBT* tree){
    RBTNode* temp = RBTNodeMax(tree, tree->root);
    if (temp == tree->nil) printf("\n");
    else printf("%s\n", temp->val);
    return temp;
}

RBTNode* RBTNodeSuccessor(RBT* tree, RBTNode* node){
    if (node == tree->nil) return node;
    else if (node->r != tree->nil){
        return RBTNodeMin(tree, node->r);
    }
    RBTNode* temp = node->p;
    while (temp != tree->nil && node == temp->r){
        node = temp;
        temp = temp->p;
    }
    return temp;
}

RBTNode* RBTSuccessor(RBT* tree, char* val){
    RBTNode* valNode = RBTNodeSearch(tree, tree->root, val);
    RBTNode* temp = RBTNodeSuccessor(tree, valNode);
    free(valNode);
    if (temp == tree->nil) printf("\n");
    else printf("%s\n", temp->val);
    return temp;
}

/*void RBTTransplant(RBT* tree, RBTNode* node, RBTNode* node2){
    if (node->p == tree->nil) tree->root = node2;
    else if (node == node->p->l) node->p->l = node2;
    else if (node == node->p->r) node->p->r = node2;
    node2->p = node->p;
}

void RBTDeleteFixup(RBT* tree, RBTNode* node){
    while (node != tree->root && node->color == BLACK){
        if(node == node->p->l){
            RBTNode* w = node->p->r;
            if (w->color == RED){
                w->color = BLACK;
                node->p->color = RED;
                RBTLeftRotate(tree, node->p);
                w = node->p->r;
            }
            if (w->l->color == BLACK && w->r->color == BLACK){
                w->color = RED;
                node = node->p;
            } else {
                if (w->r->color == BLACK){
                    w->l->color = BLACK;
                    w->color = RED;
                    RBTRightRotate(tree, w);
                    w = node->p->r;
                }
                w->color = node->p->color;
                node->p->color = BLACK;
                w->r->color = BLACK;
                RBTLeftRotate(tree, node->p);
                node = tree->root;
            }
        } else if (node->p != tree->nil){
            RBTNode* w = node->p->l;
            if (w->color == RED){
                w->color = BLACK;
                node->p->color = RED;
                RBTRightRotate(tree, node->p);
                w = node->p->l;
            }
            if (w->r->color == BLACK && w->l->color == BLACK){
                w->color = RED;
                node = node->p;
            } else {
                if (w->l->color == BLACK){
                    w->r->color = BLACK;
                    w->color = RED;
                    RBTLeftRotate(tree, w);
                    w = node->p->l;
                }
                w->color = node->p->color;
                node->p->color = BLACK;
                w->l->color = BLACK;
                RBTRightRotate(tree, node->p);
                node = tree->root;
            }
        }
    }
}

void RBTNodeDelete(RBT* tree, RBTNode* node){
    RBTNode* y = node;
    RBTNode* x = NULL;
    short yColor = y->color;
    if (node->l == tree->nil){
        x = node->r;
        RBTTransplant(tree, node, node->r);
    } else if (node->r == tree->nil){
        x = node->l;
        RBTTransplant(tree, node, node->l);
    } else {
        y = RBTNodeSuccessor(tree, node);
        yColor = y->color;
        x = y->r;
        if (y->p == node) x->p = y;
        else {
            RBTTransplant(tree, y, y->r);
            y->r = node->r;
            y->r->p = y;
        }
        RBTTransplant(tree, node, y);
        y->l = node->l;
        y->l->p = y;
        y->color = node->color;
    }
    if (yColor == BLACK){
        //RBTDeleteFixup(tree, x);
    }
    free(node);
}*/

void RBTNodeDelete(RBT* tree, RBTNode* X){
    RBTNode *W, *Y, *Z;

    if ((X->l == tree->nil) || (X->r == tree->nil))
        Y = X;
    else
        Y = RBTNodeSuccessor(tree, X);

    if (Y->l != tree->nil)
        Z = Y->l;
    else
        Z = Y->r;

    Z->p = Y->p;

    if (Y->p == tree->nil)
        tree->root = Z;
    else if (Y == Y->p->l)
        Y->p->l = Z;
    else
        Y->p->r = Z;

    if (Y != X)
        X->val = Y->val;

    if (Y->color == BLACK) // Naprawa
        while ((Z != tree->root) && (Z->color == BLACK))
            if (Z == Z->p->l)
            {
                W = Z->p->r;

                if (W->color == RED)
                { // Przypadek 1
                    W->color = BLACK;
                    Z->p->color = RED;
                    RBTLeftRotate(tree, Z->p);
                    W = Z->p->r;
                }

                if ((W->l->color == BLACK) && (W->r->color == BLACK))
                { // Przypadek 2
                    W->color = RED;
                    Z = Z->p;
                    continue;
                }

                if (W->r->color == BLACK)
                { // Przypadek 3
                    W->l->color = BLACK;
                    W->color = RED;
                    RBTRightRotate(tree, W);
                    W = Z->p->r;
                }

                W->color = Z->p->color; // Przypadek 4
                Z->p->color = BLACK;
                W->r->color = BLACK;
                RBTLeftRotate(tree, Z->p);
                Z = tree->root;
            }
            else
            { // Przypadki lustrzane
                W = Z->p->l;

                if (W->color == RED)
                { // Przypadek 1
                    W->color = BLACK;
                    Z->p->color = RED;
                    RBTRightRotate(tree, Z->p);
                    W = Z->p->l;
                }

                if ((W->l->color == BLACK) && (W->r->color == BLACK))
                { // Przypadek 2
                    W->color = RED;
                    Z = Z->p;
                    continue;
                }

                if (W->l->color == BLACK)
                { // Przypadek 3
                    W->r->color = BLACK;
                    W->color = RED;
                    RBTLeftRotate(tree, W);
                    W = Z->p->l;
                }

                W->color = Z->p->color; // Przypadek 4
                Z->p->color = BLACK;
                W->l->color = BLACK;
                RBTRightRotate(tree, Z->p);
                Z = tree->root; 
            }

    Z->color = BLACK;

    free(Y);
}

int RBTDelete(RBT* tree, char* val){
    RBTNode* delNode = RBTNodeSearch(tree, tree->root, val);
    if (delNode != tree->nil){
        tree->size -= 1;
        RBTNodeDelete(tree, delNode);
        tree->data[1]++;
        return 1;
    }
    return 0;
}
