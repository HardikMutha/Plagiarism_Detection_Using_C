/*
    This file contains the function to get the file type from the file name.
    User can input various file types like .txt, .pdf, .docx, .c, .cpp, .java, .py, .js
    However only .c and .txt files are considered to be valid for the project.
    Rest all files are ignored.
*/

#define SIZE 8

// Enum stores the file types in the form of numbers from 1 to 8

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

/*
    Pure Function: getFileType
    This function takes in a filename as input.
    Then using string manipulation, it extracts the file type from the filename.
*/

FileType getFileType(char *filename)
{
    char fileType[SIZE];
    int len = strlen(filename);
    int i, j;
    for (int k = len - 1; k >= 0; k--)
    {
        /*
            Filenames are usually in the format of name.type
            So, we need to extract the type from the filename.
            We start from the end of the filename and keep moving towards the start.
            We keep moving until we find the '.' character.
        */
        if (filename[k] == '.') // Keep checking until the '.' is found
        {
            i = k;
            break;
        }
    }
    for (j = 0; j < SIZE && i < len; j++, i++)
        fileType[j] = filename[i]; // Extract the file type and stroe it in fileType
    fileType[j] = '\0';

    // Check and compare file type and return the corresponding number

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
        return -1; // if file type is not valid, return -1
}
