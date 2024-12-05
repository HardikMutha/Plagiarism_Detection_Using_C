typedef struct Node {
    Token Data;
    TokenType type;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

Queue *createQueue();
void enqueue(Queue *q, Token data, TokenType type);
Token dequeue(Queue *q);
int isEmpty(Queue *q);
void deleteQueue(Queue *q);
void printQueue(Queue *q);
