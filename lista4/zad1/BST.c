#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "BST.h"

BSTNode* newBSTNode(char val[], BSTNode* p){
    BSTNode* newBSTNode = malloc(sizeof(BSTNode));
    newBSTNode->p = p;
    newBSTNode->r = NULL;
    newBSTNode->l = NULL;
    newBSTNode->val = val;
    return newBSTNode;
}

BST* newBST(){
    BST* newBST = malloc(sizeof(BST));
    newBST->root = NULL;
    newBST->size = 0;
    newBST->maxSize = 0;
    newBST->data[0] = 0;
    newBST->data[1] = 0;
    newBST->data[2] = 0;
    return newBST;
}

int BSTNodeInsert(BSTNode* node, char* val){
    if (strcmp(val, node->val) < 0){
        if (node->l == NULL){
            BSTNode* tempNode = newBSTNode(val, node);
            node->l = tempNode;
        } else return BSTNodeInsert(node->l, val);
    } else if (strcmp(val, node->val) >= 0){
        if (node->r == NULL){
            BSTNode* tempNode = newBSTNode(val, node);
            node->r = tempNode;
        } else return BSTNodeInsert(node->r, val);
    }
    return 1;
}

void BSTInsert(BST* tree, char* val){
    if (tree->root == NULL){
        BSTNode* tempNode = newBSTNode(val, NULL);
        tree->root = tempNode;
        tree->size++;
    } else {
        tree->size += BSTNodeInsert(tree->root, val);
    }
    tree->data[0]++;
    if (tree->size > tree->maxSize) tree->maxSize = tree->size;
}

void BSTNodeInOrderWalk(BSTNode* node){
    if (node != NULL){
        BSTNodeInOrderWalk(node->l);
        printf("%s ", node->val);
        BSTNodeInOrderWalk(node->r);
    }
}

void BSTInOrderWalk(BST* tree){
    BSTNodeInOrderWalk(tree->root);
    printf("\n");
}

void BSTLoad(BST* tree, char* filename){
    char* buffer = getWords(filename);
    char* token = strsep(&buffer, " ,-;:.*\t\b\n");
    while (token) {
        if (strcmp(token, "")!=0){
            BSTInsert(tree, token);
        }
        token = strsep(&buffer, " ,-;:.*\t\b\n");
    }
}

BSTNode* BSTNodeSearch(BSTNode* node, char* val){
    if (node == NULL || strcmp(val, node->val) == 0) return node;
    else if (strcmp(val, node->val) < 0) return BSTNodeSearch(node->l, val);
    else return BSTNodeSearch(node->r, val);
}

BSTNode* BSTSearch(BST* tree, char* val){
    BSTNode* tempNode = BSTNodeSearch(tree->root, val);
    if (tempNode == NULL) printf("0\n");
    else printf("1\n");
    tree->data[2]++;
    return tempNode;
}

BSTNode* BSTNodeMin(BSTNode* node){
    if (node == NULL) return node;
    else if (node->l == NULL) return node;
    return BSTNodeMin(node->l);
}

BSTNode* BSTMin(BST* tree){
    BSTNode* temp = BSTNodeMin(tree->root);
    if (temp == NULL) printf("\n");
    else printf("%s\n", temp->val);
    return temp;
}

BSTNode* BSTNodeMax(BSTNode* node){
    if (node == NULL) return node;
    else if (node->r == NULL) return node;
    return BSTNodeMax(node->r);
}

BSTNode* BSTMax(BST* tree){
    BSTNode* temp = BSTNodeMax(tree->root);
    if (temp == NULL) printf("\n");
    else printf("%s\n", temp->val);
    return temp;
}

BSTNode* BSTNodeSuccessor(BSTNode* node){
    if (node == NULL) return node;
    else if (node->r != NULL){
        return BSTNodeMin(node->r);
    }
    BSTNode* temp = node->p;
    while (temp != NULL && node == temp->r){
        node = temp;
        temp = temp->p;
    }
    return temp;
}

BSTNode* BSTSuccessor(BST* tree, char* val){
    BSTNode* valNode = BSTNodeSearch(tree->root, val);
    BSTNode* temp = BSTNodeSuccessor(valNode);
    free(valNode);
    if (temp == NULL) printf("\n");
    else printf("%s\n", temp->val);
    free(temp);
}

int BSTNodeDelete(BSTNode* node){
    if (node == NULL) return 0;
    else if (node->l == NULL && node->r == NULL) {
        if (node->p != NULL){
            if (node->p->l == node) node->p->l = NULL;
            else node->p->r = NULL;
        }
        free(node);
        return 1;
    } else if (node->l == NULL) {
        if (node->p != NULL){
            if (node->p->l == node) node->p->l = node->r;
            else node->p->r = node->r;
            node->r->p = node->p;
        }
        free(node);
        return 1;
    } else if (node->r == NULL){
        if (node->p != NULL){
            if (node->p->l == node) node->p->l = node->l;
            else node->p->r = node->l;
            node->l->p = node->p;
        }
        free(node);
        return 1;
    } else {
        BSTNode* succ = BSTNodeSuccessor(node);
        node->val = succ->val;
        return BSTNodeDelete(succ);
    }
}

void BSTDelete(BST* tree, char* val){
    tree->size -= BSTNodeDelete(BSTNodeSearch(tree->root, val));
    tree->data[1]++;
}
