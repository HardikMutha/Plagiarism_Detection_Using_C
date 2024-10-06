
typedef struct node
{
    char *val;
    struct node *next;
} node;

typedef struct list // struct for linked list with head pointer
{
    node *head;
    int len; // stores the lenght of the linked list
} list;

void init_SLL(list *l);
void append(list *l, char *val);
void traverse(list l);
void insert_at_beg(list *l, char *val);
void remove_at_beg(list *l);
