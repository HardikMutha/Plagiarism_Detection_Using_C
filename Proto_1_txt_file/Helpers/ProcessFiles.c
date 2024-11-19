#define SIZE 8

typedef enum
{
    TXT = 1,
    PDF,
    DOCX,
    C,
    CPP,
    JAVA,
    PYTHON,
    JAVASCRIPT
} FileType;
FileType getFileType(char *filename);

FileType getFileType(char *filename)
{
    char fileType[SIZE];
    int len = strlen(filename);
    int i, j;
    for (int k = len - 1; k >= 0; k--)
    {
        if (filename[k] == '.')
        {
            i = k;
            break;
        }
    }
    for (j = 0; j < SIZE && i < len; j++, i++)
        fileType[j] = filename[i];
    fileType[j] = '\0';
    if (strcmp(fileType, ".txt") == 0)
        return 1;
    else if (strcmp(fileType, ".pdf") == 0)
        return 2;
    else if (strcmp(fileType, ".docx") == 0)
        return 3;
    else if (strcmp(fileType, ".c") == 0)
        return 4;
    else if (strcmp(fileType, ".cpp") == 0)
        return 5;
    else if (strcmp(fileType, ".java") == 0)
        return 6;
    else if (strcmp(fileType, ".py") == 0)
        return 7;
    else if (strcmp(fileType, ".js") == 0)
        return 8;
    else
        return -1;
}
