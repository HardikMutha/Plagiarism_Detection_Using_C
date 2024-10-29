/*
    Structure of Doubly Linked List -
    Each Node in the DLL contains a pointer to a list and a flag.
    Flag is reponsible for marking the list when a sufficient number of tokens from the list match with
    list in other program and thus will possibly Plagiarised.
    The DLL will be responsible for storing the headers of the linked list.
*/

typedef struct nodeDLL
{
    list *l;
    int flag;
    struct nodeDLL *prev;
    struct nodeDLL *next;
} nodeDLL;

typedef struct DLL
{
    nodeDLL *front;
    nodeDLL *rear;
    int DLL_length;
} DLL;

void initDLL(DLL *l);
void insertNode_DLL(DLL *dll, list *l);
void removeNode_DLL(DLL *dll, nodeDLL *node);
void deleteDLL(DLL *dll);
void traverse_DLL(DLL l);
