#include "..\SLL\sll.h"

typedef struct nodeDLL{
    nodeSLL *head;
    int flag;
    int len;
    struct nodeDLL *prev;
    struct nodeDLL *next;
}nodeDLL;

typedef struct DLL{
    nodeDLL *front;
    nodeDLL *rear;
}DLL;

void init(DLL *l);
void insertNode(DLL *l, nodeSLL *head);
void removeNode(DLL *l, nodeDLL *node);
void deleteDLL(DLL *l);
