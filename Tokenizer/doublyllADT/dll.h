/*
 * Doubly Linked List:
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

typedef struct dllnode {
    char *str;
    struct dllnode *left;
    struct dllnode *right;
} dllnode;

typedef struct dll {
    dllnode *front;
    dllnode *rear;
    int len;
} dll;

void init_dll(dll *l);
void append_dll(dll *l, char *input);
void traverse_dll(dll l);
