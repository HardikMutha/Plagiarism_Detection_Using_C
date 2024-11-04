#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sll.h"

void init_SLL(list *l)
{
    l->head = NULL;
    l->len = 0;
    return;
}

void append_SLL(list *l, char *node_val, TokenType T_type)
{
    int stringlen = strlen(node_val);
    listnode *newNode = (listnode *)malloc(sizeof(listnode));
    newNode->next = NULL;
    newNode->val = (char *)malloc(sizeof(char) * (stringlen + 2));
    strcpy(newNode->val, node_val);
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

void traverse_SLL(list l)
{
    listnode *temp = l.head;
    while (temp)
    {
        printf("%s ", temp->val);
        printf("%d ", temp->type);
        temp = temp->next;
    }
    return;
}

void delete_SLL(list *l)
{
    listnode *temp = l->head;
    listnode *curr = temp;
    while (temp)
    {
        curr = temp->next;
        free(temp->val);
        free(temp);
        temp = curr;
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