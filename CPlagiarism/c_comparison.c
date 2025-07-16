#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include "../utils/SLL/sll.h"
#include "../utils/DLL/dll.h"
#include "./compare_lists.c"
#include "generateGraph.c"
void writeToHTML(int numberFiles);

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
    char line[1024];
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

/*
    This function takes an array of filenames, integer to store the number of files
    and a directory name as input
    In the function, directory is opened and all the filenames are updated in the array
    The number of files is also updated
*/
void readFileNameWithoutUpdation(char filenames[][128], int *numfiles, char *dir_name)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(dir_name);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                strcpy(filenames[*numfiles], dir->d_name);
                (*numfiles)++;
            }
        }
        closedir(d);
    }
    return;
}

/*
    Custom data Structure to store the similarity pairs of files.
    This data structure stores the names of the all the other files with which the current file is being compared.
    It also stores the similarity score of the current file with all the other files.
    The length of the structure is also stored.
*/
typedef struct Similarity_Pair
{
    char filenames[256][128];
    double simscore[256];
    int len;
} Similarity_Pair;

int main(int argc, char const *argv[])
{
    if (argc < 1)
    {
        fprintf(stderr, "Invalid Number of Arguments\n");
        return -1;
    }
    system("mkdir CPlagiarism/Output_Graphs -p"); // Create a directory to store the output graphs
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1)
    {
        perror("Error Opening the File\n");
        return errno;
    }
    char originalFilenames[128][128]; // This Stores the original Filenames to be used as graph labels
    int originalFilenamesLen = 0;
    readFileNameWithoutUpdation(originalFilenames, &originalFilenamesLen, argv[2]); // Store raw filenames in the originalfileName array
    FILE *fptr = fopen("./Outputs/FileNames.txt", "r");                             // Open the file containing the filenames
    if (fptr == NULL)
        printf("Null\n");
    char filenames[128][64]; // This array stores the updated filenames (output files of the tokenizer)
    int numfiles = 0;
    while (fscanf(fptr, "%s", filenames[numfiles]) > 0)
        numfiles++;
    DLL AllTokenHeaders[numfiles]; // Array of DLL to store the tokenized output of all the files
    for (int i = 0; i < numfiles; i++)
    {
        initDLL(&AllTokenHeaders[i]);                                  // Initialize the DLL
        insertListHeaders_into_DLL(filenames[i], &AllTokenHeaders[i]); // Insert the list headers into the DLL
    }
    Similarity_Pair files_similarity_pairs[numfiles]; // Array of Similarity_Pair to store the similarity pairs of files
    // Initialize the length of the Similarity_Pair
    for (int i = 0; i < numfiles; i++)
        files_similarity_pairs[i].len = 0;

    for (int i = 0; i < numfiles; i++)
    {
        for (int j = i + 1; j < numfiles; j++)
        {
            double final_ans1, final_ans2; // Variables to store the final similarity score of the files
            // Compare the files and get the similarity score
            compare_files(&AllTokenHeaders[i], &AllTokenHeaders[j], &final_ans1, &final_ans2);
            // required updations to store the similarity pairs of file i with respect to file j
            int curr_len = files_similarity_pairs[i].len;
            strcpy(files_similarity_pairs[i].filenames[curr_len], originalFilenames[j]);
            files_similarity_pairs[i].simscore[curr_len] = final_ans1;
            files_similarity_pairs[i].len++;

            // printf("Similarity of file %s w.r.t to file %s is = %.2lf\n", filenames[i], filenames[j], (final_ans * 100));

            // required updations to store the similarity pairs of file j with respect to file i
            curr_len = files_similarity_pairs[j].len;
            strcpy(files_similarity_pairs[j].filenames[curr_len], originalFilenames[i]);
            files_similarity_pairs[j].simscore[curr_len] = final_ans2;
            files_similarity_pairs[j].len++;
            // printf("Similarity of file %d w.r.t to file %d is = %.2lf\n", (j + 1), (i + 1), (final_ans * 100));
        }
        // Free the allocated memory for the ith DLL after comparison with all other files is completed
        deleteDLL(&AllTokenHeaders[i]);
    }
    for (int i = 0; i < numfiles; i++)
    {
        // Generate the graph for all the files.
        generateGraph(originalFilenames[i], files_similarity_pairs[i].filenames, files_similarity_pairs[i].simscore, files_similarity_pairs[i].len, i + 1);
    }
    writeToHTML(numfiles); // Write the output to the HTML file
    printf("index.html is generated in CPlagiarism folder\n");
    return 0;
}

/*
    This function takes the number of files as input and writes the output to the HTML file
    The function generates the HTML code dynamically and accesses the generated graphs to display in the HTML file
*/
void writeToHTML(int numberFiles)
{
    // Initialize the HTML code
    char init_Code[8192] = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"/><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" /><title>PlagCheck Results</title><link rel=\"stylesheet\" href=\"./style.css\"><style>*{margin: 0;padding: 0;box-sizing: border-box;}h1 {text-align: center;}</style></head><body><h1>Results for Plagiarism Check</h1>";
    for (int i = 0; i < numberFiles; i++)
    {
        // Dynamically using the generated graphs in the HTML file
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
    FILE *fptr = fopen("./CPlagiarism/index.html", "w"); // open the file to write the HTML code
    fprintf(fptr, "%s", init_Code);                      // Write the HTML code to the file
    fclose(fptr);
    return;
}
