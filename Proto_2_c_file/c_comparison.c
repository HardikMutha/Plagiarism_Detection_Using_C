#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "SLL/sll.h"
#include "./DLL/dll.h"
#include "./compare_lists.c"

// This Function reads lines individually from the tokenized output File
int read_line(int fd, char *buf)
{
    char ch;
    int i = 0;
    while (read(fd, &ch, 1))
    {
        if (ch == '\n')
        {
            buf[i] = '\0';
            break;
        }
        buf[i++] = ch;
    }
    return i;
}

/*
    This Function expects a token type corresponding to TokenType Enum and a token val
    It then appends the token to the linked list.
*/

int insertLines_into_list(int fd, list *l, char *token_val, char *token_type)
{
    append_SLL(l, token_val, get_type(token_type));
    return 1;
}

/*
This function is responsible for insertion of the list headers into the DLL
    -> First read line is called to get lines from the tokenized output file
    -> The token type and token value are extracted from the line using strtok
    -> If the token type is SpDelim then the list is inserted into the DLL
    -> A new list is then initialized to store the next set of tokens
*/

void insertListHeaders_into_DLL(int fd, DLL *AllTokenHeaders)
{
    char line[128];
    list *l = (list *)malloc(sizeof(list));
    list *temp = l;
    int cnt = 0;
    /*
        To avoid insertion of Empty List in case of Two Consecutive Special Delimiters,
        a counter is initialized
    */
    while (read_line(fd, line))
    {
        char *token_type = strtok(line, " ");
        char *token_val = strtok(NULL, " ");
        if (strcmp(token_type, "SpDelim") == 0)
        {
            if (cnt == 0)
                continue;
            insertNode_DLL(AllTokenHeaders, temp);
            temp = (list *)malloc(sizeof(list));
            cnt = 0;
        }
        else
        {
            insertLines_into_list(fd, temp, token_val, token_type);
            cnt++;
        }
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Invalid Number of Arguments\n");
        return -1;
    }
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1)
    {
        perror("Error Opening the File\n");
        return errno;
    }
    int fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1)
    {
        perror("Error Opening the File\n");
        return errno;
    }
    DLL AllTokenHeaders1, AllTokenHeaders2;
    initDLL(&AllTokenHeaders1);
    insertListHeaders_into_DLL(fd1, &AllTokenHeaders1);
    initDLL(&AllTokenHeaders2);
    insertListHeaders_into_DLL(fd2, &AllTokenHeaders2);
    double matched_lines = compare_files(&AllTokenHeaders1, &AllTokenHeaders2);
    double final_ans = get_final_ans(&AllTokenHeaders1, matched_lines);
    printf("Final Ans = %.3lf\n", final_ans);
    return 0;
}
