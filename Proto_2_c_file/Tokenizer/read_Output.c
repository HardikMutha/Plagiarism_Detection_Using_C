#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_TOKEN_VALUE 100

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
    TOKEN_KEYINT,
    TOKEN_KEYFLOAT,
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

void init_SLL(list *l)
{
    l->head = NULL;
    l->len = 0;
    return;
}

void append(list *l, char *val, TokenType T_type)
{
    int stringlen = strlen(val);
    listnode *newNode = (listnode *)malloc(sizeof(listnode));
    newNode->next = NULL;
    newNode->val = (char *)malloc(sizeof(char) * (stringlen + 2));
    strcpy(newNode->val, val);
    newNode->type = T_type;
    if (l->head == NULL)
    {
        l->head = newNode;
        l->len++;
    }
    else
    {
        listnode *temp = l->head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
        l->len++;
    }
    return;
}

void traverse(list l)
{
    listnode *temp = l.head;
    while (temp)
    {
        printf("%s ", temp->val);
        if (temp->type == TOKEN_SPDELIM)
            printf("\n");
        temp = temp->next;
    }
    return;
}

TokenType get_type(char *buf)
{

    if (strcmp(buf, "Preprocessor") == 0)
        return 0;
    if (strcmp(buf, "Delimiter") == 0)
        return 1;
    if (strcmp(buf, "SpecialCharacters") == 0)
        return 2;
    if (strcmp(buf, "Assign") == 0)
        return 3;
    if (strcmp(buf, "Arithmatic") == 0)
        return 4;
    if (strcmp(buf, "Logical") == 0)
        return 5;
    if (strcmp(buf, "Relational") == 0)
        return 6;
    if (strcmp(buf, "Keyword") == 0)
        return 7;
    if (strcmp(buf, "Function") == 0)
        return 8;
    if (strcmp(buf, "Identifier") == 0)
        return 9;
    if (strcmp(buf, "Fraction") == 0)
        return 10;
    if (strcmp(buf, "NegativeFraction") == 0)
        return 11;
    if (strcmp(buf, "Integer") == 0)
        return 12;
    if (strcmp(buf, "NegativeInteger") == 0)
        return 13;
    if (strcmp(buf, "Constant") == 0)
        return 14;
    if (strcmp(buf, "String") == 0)
        return 15;
    if (strcmp(buf, "INT") == 0)
        return 16;
    if (strcmp(buf, "FLOAT") == 0)
        return 17;
    if (strcmp(buf, "SpDelim") == 0)
        return 18;
    return -1;
}

int get_val(char *input, char *val)
{
    /* printf("input: %s\n", input); */
    int i = 0, j = 0;
    while (input[i++] != ' ')
        ;
    while (input[i])
        val[j++] = input[i++];
    val[j] = '\0';
    /* printf("val: %s\n", val); */
    return 1;
}

int read_line(int fd, char *buf)
{
    char ch;
    int i = 0;
    while (read(fd, &ch, 1))
    {
        if (ch == '\n')
            break;
        buf[i++] = ch;
    }
    buf[i] = '\0';
    return i;
}

int read_file(int fd, char *filename, list *l)
{
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open failed");
        return errno;
    }
    char buf[100], val[100];
    int tokens = 0;
    TokenType type;
    while (read_line(fd, buf))
    {
        /* printf("buf: %s\n", buf); */
        type = get_type(buf);
        if (type == 0)
            continue;
        get_val(buf, val);
        append(l, val, type);
        tokens++;
    }
    return tokens;
}

int main(int argc, char *argv[])
{
    int fd = 0;
    if (argc < 2)
    {
        printf("invalid input file\n");
        return -1;
    }
    list l;
    init_SLL(&l);
    int n = read_file(fd, argv[1], &l);
    printf("tokens: %d\n", n);
    traverse(l);
    return 0;
}
