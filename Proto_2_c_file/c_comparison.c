#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "SLL/sll.h"
#include "./DLL/dll.h"
#include "./compare_lists.c"
#include "generateGraph.c"
/* #include "writeHTML.c" */

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

void insertListHeaders_into_DLL(char *filename, DLL *AllTokenHeaders)
{
    char *file = (char *)malloc(sizeof(char) * 128);
    strcpy(file, "./Outputs/Tests/");
    strcat(file, filename);
    int fd = open(file, O_RDONLY);
    free(file);
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

void writeToHTML(int numberFiles);

typedef struct Similarity_Pair
{
    char filenames[256][64];
    double simscore[256];
    int len;
} Similarity_Pair;

int main(int argc, char const *argv[])
{
    system("mkdir Proto_2_c_file/Output_Graphs -p");
    if (argc < 1)
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
    FILE *fptr = fopen("./Outputs/FileNames.txt", "r");
    if (fptr == NULL)
        printf("Null\n");
    char filenames[128][64];
    int numfiles = 0;
    while (fscanf(fptr, "%s", filenames[numfiles]) > 0)
        numfiles++;
    DLL AllTokenHeaders[numfiles];
    for (int i = 0; i < numfiles; i++)
    {
        initDLL(&AllTokenHeaders[i]);
        insertListHeaders_into_DLL(filenames[i], &AllTokenHeaders[i]);
    }
    Similarity_Pair files_similarity_pairs[numfiles];
    for (int i = 0; i < numfiles; i++)
        files_similarity_pairs[i].len = 0;

    for (int i = 0; i < numfiles; i++)
    {
        for (int j = i + 1; j < numfiles; j++)
        {
            double matched_lines = compare_files(&AllTokenHeaders[i], &AllTokenHeaders[j]);
            double final_ans = get_final_ans(&AllTokenHeaders[i], matched_lines);

            int curr_len = files_similarity_pairs[i].len;
            strcpy(files_similarity_pairs[i].filenames[curr_len], filenames[j]);
            files_similarity_pairs[i].simscore[curr_len] = final_ans;
            files_similarity_pairs[i].len++;

            // printf("Similarity of file %s w.r.t to file %s is = %.2lf\n", filenames[i], filenames[j], (final_ans * 100));

            matched_lines = compare_files(&AllTokenHeaders[j], &AllTokenHeaders[i]);
            final_ans = get_final_ans(&AllTokenHeaders[j], matched_lines);
            curr_len = files_similarity_pairs[j].len;
            strcpy(files_similarity_pairs[j].filenames[curr_len], filenames[i]);
            files_similarity_pairs[j].simscore[curr_len] = final_ans;
            files_similarity_pairs[j].len++;
            // printf("Similarity of file %d w.r.t to file %d is = %.2lf\n", (j + 1), (i + 1), (final_ans * 100));
        }
        deleteDLL(&AllTokenHeaders[i]);
    }
    for (int i = 0; i < numfiles; i++)
    {
        generateGraph(filenames[i], files_similarity_pairs[i].filenames, files_similarity_pairs[i].simscore, files_similarity_pairs[i].len, i + 1);
    }
    writeToHTML(numfiles);
    /* system("open ./index.html"); */
    printf("index.html is generated in Proto_2_c_file folder\n");
    return 0;
}


void writeToHTML(int numberFiles)
{
    char init_Code[8192] = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"/><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" /><title>PlagCheck Results</title><style>*{margin: 0;padding: 0;box-sizing: border-box;}h1 {text-align: center;}</style></head><body><h1>Results for Plagiarism Check</h1>";
    for (int i = 0; i < numberFiles; i++)
    {
        char tempName[128] = "./Output_Graphs/";
        char x[16];
        intToStr(i + 1, x);
        strcat(tempName, "Graph");
        strcat(tempName, x);
        strcat(tempName, ".png");
        strcat(init_Code, "<p><img src=\"");
        strcat(init_Code, tempName);
        strcat(init_Code, "\"/></p>");
    }
    strcat(init_Code, "</body></html>");
    FILE *fptr = fopen("./Proto_2_c_file/index.html", "w");
    fprintf(fptr, "%s", init_Code);
    fclose(fptr);
    return;
}
