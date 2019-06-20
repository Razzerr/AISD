/*typedef struct Trunk{
    struct Trunk *prev;
    char *str;
} Trunk;

Trunk *newTrunk(Trunk *prev, char *str){
    Trunk *temp = malloc(sizeof(Trunk));
    temp->prev = prev;
    temp->str = str;
    return temp;
}

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p){
    if (p == NULL)
        return;
    showTrunks(p->prev);
    printf("%s", p->str);
}

// Recursive function to print binary tree. It uses inorder traversal
// call as printTree(root, nullptr, false);
void printTree(RBT* tree, RBTNode *root, Trunk *prev, short isLeft){
    if (root == tree->nil)
        return;

    char *prev_str = "   ";
    Trunk *trunk = newTrunk(prev, prev_str);
    printTree(tree, root->l, trunk, 1);

    if (!prev)
        trunk->str = "--";
    else if (isLeft == 1)
    {
        trunk->str = ".--";
        prev_str = "  |";
    }
    else
    {
        trunk->str = "`--";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    printf("%s (%i)\n", root->val, root->color);
    if (prev)
        prev->str = prev_str;

    trunk->str = "  |";
    printTree(tree, root->r, trunk, 0);
}*/