/*
    The List contains nodes of type listnode and lenght of the list.
    Each listnode contains a value and a type and a next_pointer.
    Various Possible Token Types are defined in the enum TokenType.

    A single List will be reponsible for continuoslly storing the tokens
    until a special delimiter is encountered. At that point the list header will be
    inserted into the DLL.
    A new linked list will be created to store the next set of tokens.
*/

typedef enum
{
    TOKEN_PREPCROCESS = 0,
    TOKEN_DELIM,
    TOKEN_SPCHAR,
    TOKEN_ASSIGN,
    TOKEN_ARITHMATIX,
    TOKEN_LOGICAL,
    TOKEN_RELATIONAL,
    TOKEN_KEYWORD,
    TOKEN_FUNCTION,
    TOKEN_IDENTIFIER,
    TOKEN_FRACT,
    TOKEN_NEGFRACT,
    TOKEN_INT,
    TOKEN_NEGINT,
    TOKEN_CONSTANT,
    TOKEN_STRING,
    TOKEN_LOOP,
    TOKEN_SPDELIM
} TokenType;

typedef struct listnode
{
    char *val;
    TokenType type;
    struct listnode *next;
} listnode;

typedef struct list
{
    listnode *head;
    int len;
} list;

void init_SLL(list *l);
void append_SLL(list *l, char *node_val, TokenType T_type);
void traverse_SLL(list l);
void delete_SLL(list *l);
TokenType get_type(char *buf);
