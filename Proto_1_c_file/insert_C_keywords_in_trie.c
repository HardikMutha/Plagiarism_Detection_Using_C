#include "./trie_ADT/trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int insertCSVintoTrie(const char *filename, trie *t)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error Opening the File");
        return errno;
    }
    char ch, buf[48];
    int i = 0;
    while (read(fd, &ch, 1) > 0)
    {
        if (ch == ',')
        {
            buf[i] = '\0';
            insertWord(t, buf);
            i = 0;
        }
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
        {
            buf[i++] = ch;
        }
    }
    return 1;
}

// int main(int argc, char *argv[]){
//     trie t;
//     createNode(&t);
//     char str[64];
//     insertCSVintoTrie(argv[1], &t);
//     displayTrie(t, str, 0);
//     freeTrie(&t);
//     return 0;
// }