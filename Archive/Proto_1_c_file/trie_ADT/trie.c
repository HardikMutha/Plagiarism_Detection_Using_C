#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

int getBase(char ch)
{
    if(ch >= 'A' && ch <= 'Z')
        return 65;
    else if(ch >= 'a' && ch <= 'z')
        return 70;
    else if(ch == '_')
        return 69;
    return -1;
}

int containsKey(node *p, char ch, int base)
{
    return (p->links[(int)ch - base] != NULL);
}

void createNode(trie *t)
{
    *t = (node *)calloc(1, sizeof(node));
    return;
}

void insertWord(trie *t, char *data)
{
    int len = strlen(data);
    int base = 0;
    if (len == 0)
        return;
    node *p = *t;
    for (int i = 0; i < len; i++)
    {
        base = getBase(data[i]);
        if(base == -1)
            return;
        if (containsKey(p, data[i], base))
            p = p->links[(int)data[i] - base];
        else
        {
            createNode(&p->links[(int)data[i] - base]);
            p = p->links[(int)data[i] - base];
        }
    }
    p->isEndOfWord = 1;
    return;
}

int searchWord(trie t, char *key)
{
    int len = strlen(key);
    int base = 0;
    if (len == 0)
        return 0;
    node *p = t;
    for (int i = 0; i < len; i++)
    {
        base = getBase(key[i]);
        if(base == -1)
            return 0;
        if (!containsKey(p, key[i], base))
            return 0;
        p = p->links[(int)key[i] - base];
    }
    if (!p->isEndOfWord)
        return 0;
    return 1;
}

int startsWith(trie t, char *key)
{
    int len = strlen(key);
    int base = 0;
    if (len == 0)
        return 0;
    node *p = t;
    for (int i = 0; i < len; i++)
    {
        base = getBase(key[i]);
        if(base == -1)
            return 0;
        if (!containsKey(p, key[i], base))
            return 0;
        p = p->links[(int)key[i] - base];
    }
    return 1;
}

void displayTrie(trie t, char *prefix, int length)
{
    if (t == NULL)
        return;
    if (t->isEndOfWord)
    {
        prefix[length] = '\0';  // Null terminate the string
        printf("%s\n", prefix);
    }
    for (int i = 0; i < 53; i++)
    {
        if (t->links[i] != NULL)
        {
            if (i >= 0 && i <= 25)
                prefix[length] = 'A' + i;      // Upper-case letters ('A' to 'Z')
            else if (i == 26)
                prefix[length] = '_';          // Underscore ('_')
            else if (i >= 27 && i <= 52)
                prefix[length] = 'a' + (i - 27); // Lower-case letters ('a' to 'z')

            displayTrie(t->links[i], prefix, length + 1);
        }
    }
    return;
}


void freeTrie(trie *t)
{
    if (*t == NULL)
        return;
    for (int i = 0; i < 53; i++)
    {
        if ((*t)->links[i] != NULL)
            freeTrie(&((*t)->links[i]));
    }
    free(*t);
    *t = NULL;
    return;
}