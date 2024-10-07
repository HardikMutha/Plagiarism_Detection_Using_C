#include "linkedlist.h"
#include <stdio.h>

int main()
{
    list l1;
    char arr[128];
    init_SLL(&l1);
    while (scanf("%s", arr) > 0)
    {
        append(&l1, arr);
    }
    traverse(l1);
    insert_at_beg(&l1, "Abhijit");
    printf("\n\n");
    traverse(l1);
    remove_at_beg(&l1);
    remove_at_beg(&l1);
    printf("\n\n");
    traverse(l1);
    deleteList(&l1);
    printf("test0\n");
    return 0;
}
