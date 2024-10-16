/*
 * node *links[53];

 * struct of array of node addresses is as follows -
 * 
 * index: 0 - 25 -> 'A' to 'Z'
 * index: 26 -> '_'
 * index: 27 - 52 -> 'a' to 'z'
 * 
 * The value to be subtracted from the ascii value of given character will be decided through a func: int getBase(char ch); a variable 'base' will be used to store that value and use it get the corressponding index.
*/

typedef struct node
{
    struct node *links[53];
    int isEndOfWord;
} node;

typedef node *trie;

int getBase(char ch);
int containsKey(node *p, char ch, int base);
void createNode(trie *t);
void insertWord(trie *t, char *data);
int searchWord(trie t, char *key);
int startsWith(trie t, char *key);
void displayTrie(trie t, char *prefix, int length);
void freeTrie(trie *t);