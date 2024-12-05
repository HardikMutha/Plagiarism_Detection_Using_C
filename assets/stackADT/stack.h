typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
    int size;
} Stack;

Stack *createStack();
void push(Stack *s, int data);
Node *pop(Stack *s);
int isEmpty(Stack *s);
void printStack(Stack *s);
void freeStack(Stack *s);
