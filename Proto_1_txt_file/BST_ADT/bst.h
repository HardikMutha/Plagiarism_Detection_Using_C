typedef struct treenode
{
    char val[144];
    struct treenode *left;
    struct treenode *right;
} treenode;

typedef treenode *tree;

void initBST(tree *t);
void insertValue(tree *t, char *val);
void inOrderTraversal(tree t);
void preOrderTraversal(tree t);
void postOrderTraversal(tree t);
void deleteNode(tree *t, char *val);
int searchNode(tree t,char *val);
void destroyTree(tree *t);
/*

*/
