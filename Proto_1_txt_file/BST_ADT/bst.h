typedef struct node
{
    char val[144];
    struct node *left;
    struct node *right;
} node;

typedef node *tree;

void initBST(tree *t);
void insertValue(tree *t, char *val);
void inOrderTraversal(tree t);
void preOrderTraversal(tree t);
void postOrderTraversal(tree t);
void deleteNode(tree *t, char *val);
int searchNode(tree t,char *val);
/*

*/
