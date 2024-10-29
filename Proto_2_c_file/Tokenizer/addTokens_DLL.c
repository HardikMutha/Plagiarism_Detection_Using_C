#include "doublyllADT/dll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void add_to_buffer(char *identifier_type, char *buffer)
{
    int len = strlen(buffer);
    int i = len;
    buffer[i] = ',';
    i++;
    for (int j = 0; j < strlen(identifier_type); j++, i++)
    {
        buffer[i] = identifier_type[j];
    }
    buffer[i] = '\0';
    return;
}

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

int read_file(int fd, char *filename, dll *l)
{
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Failed to Open the file");
        return errno;
    }
    char line[128];
    int tokens = 0;
    char buffer[512];
    buffer[0] = '\0';
    while (read_line(fd, line))
    {
        char *identifier_type = strtok(line, " ");
        // printf("%s\n", identifier_type);
        if (strcmp(identifier_type, "SpDelim") != 0)
        {
            add_to_buffer(identifier_type, buffer);
        }
        else
        {
            printf("%s\n", buffer);
            buffer[0] = '\0';
        }
        tokens++;
    }
    return tokens;
}

int main(int argc, char *argv[])
{
    int fd = 0;
    if (argc < 2)
    {
        fprintf(stderr, "Invalid File Arguments\n");
        return -1;
    }
    dll l;
    init_dll(&l);
    read_file(fd, argv[1], &l);
    return 0;
}
