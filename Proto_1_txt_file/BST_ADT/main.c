#include "bst.c"

int main()
{
    tree t;
    initBST(&t);
    char a[256];
    while (scanf("%s", a) > 0)
    {
        insertValue(&t, a);
    }
    inOrderTraversal(t);
    // printf("%d\n", searchNode(t, "Hardik"));
    return 0;
}
