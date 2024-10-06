#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

void initBST(tree *t)
{
    *t = NULL;
    return;
}

void insertValue(tree *t, char *val)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->left = NULL;
    newNode->right = NULL;
    strcpy(newNode->val, val);
    if (*t == NULL)
    {
        *t = newNode;
        return;
    }
    else
    {
        node *curr = *t;
        if (strcmp(curr->val, val) > 0)
        {
            return insertValue(&(curr->left), val);
        }
        else if (strcmp(curr->val, val) < 0)
        {
            return insertValue(&(curr->right), val);
        }
    }
    return;
}

/*
Inorder Traversal involves
left root right
        [root]
        /   \
    [left]  [right]
On a BST, Inorder Traversal gives back the data in sorted Order
*/

void inOrderTraversal(tree t)
{
    if (t == NULL)
        return;
    inOrderTraversal(t->left);
    printf("%s\n", t->val);
    inOrderTraversal(t->right);
}

/*
Pre-Order Traversal -
    root left right
*/

void preOrderTraversal(tree t)
{
    if (t == NULL)
        return;
    printf("%s\n", t->val);
    preOrderTraversal(t->left);
    preOrderTraversal(t->right);
}

/*
->Post Order Traversal
    left right root
*/

void postOrderTraversal(tree t)
{
    if (t == NULL)
        return;
    postOrderTraversal(t->left);
    postOrderTraversal(t->right);
    printf("%s\n", t->val);
}

void deleteNode(tree *t, char *val)
{
}
