#include "./mainheader.h"
#include <dirent.h>
#include "./generateGraph.c"

// These variables are used to manage pdf files
char pdfFileNamesOnly[64][256];
int pdfFileNameSize = 0;

/*
    This function is responsible for handling PDFs.
    Since PDF files cannot be directly checked for string comparison,
    we need to convert them to text files.
    These text files are temporary and are deleted after the comparison.
    The function takes the filename of the PDF file as input.
    It parses the PDF file data and stores the data into a text file, which is dynamically created based on the file number.
    This text file is then used for comparison with the other files.
*/

// Coverts an integer to a string.

void check_filetypes_and_update_filenames(char *filename, int fileNumber)
{
    FileType ft = getFileType(filename);
    if (ft == 2) // Check if the file is of the type .pdf
    {
        /*
            If the file is of the type .pdf, then convert the file to text file.
            The text file is stored in the folder TextPlagiarism/Tests/PdfTempx.txt where x is the file number.
            The file is then added to the pdfFileNamesOnly array.
        */
        char newFilename[128] = "";
        system("mkdir ./TextPlagiarism/Tests -p");
        strcat(newFilename, "./TextPlagiarism/Tests/PdfTemp");
        char x[16];
        intToStr(fileNumber, x);
        // newFilename[strlen(newFilename)] = fileNumber + '0';
        // newFilename[strlen(newFilename) + 1] = '\0';
        strcat(newFilename, x);
        strcat(newFilename, ".txt");
        strcpy(pdfFileNamesOnly[pdfFileNameSize], newFilename);
        pdfFileNameSize++;
        FILE *fptr = fopen(newFilename, "w");
        if (fptr == NULL)
        {
            printf("Error Opening File\n");
            exit(1);
        }
        // Data is read from the PDF
        char *pdf_data = get_pdf_data(filename);
        // Data is pasted in the text file
        fprintf(fptr, "%s", pdf_data);
        free(pdf_data);
        strcpy(filename, newFilename);
        fclose(fptr);
        return;
    }
    return;
}

/*
    This function is used to list out all the files and folders present is a directory.
    It uses the dirent.h library to list out the files and folders.
    The function takes the following parameters:
        char filenames[][128] : A 2D array to store the filenames.
        int *num_files : A pointer to the number of files.
        char *dir_name : The name of the directory.
*/
void readFileNames(char filenames[][128], int *num_files, char *dir_name)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(dir_name); // Opens the directory
    printf("%s\n", dir_name);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            // Ignore the current and parent folder names and only read files/folders other than them.
            // The structure dirent has :
            // 1. d_name : The name of the file/folder
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                // char a[256] = "./TextPlagiarism/Tests/";
                char a[128];
                strcpy(a, dir_name);
                // The file path is passed to the realpath function to get the absolute path of the file.
                char *temp = realpath(strcat(a, dir->d_name), NULL);
                if (temp)
                {
                    strcpy(filenames[*num_files], temp);
                    check_filetypes_and_update_filenames(filenames[*num_files], *num_files); // Filename is checked for filetype and updated accordingly.
                    // PDF files are parsed and handled specially using this function
                    (*num_files)++;
                }
            }
        }
        closedir(d); // close the directory
    }
    return;
}

// This function is used to read the filenames without updating the filenames.
// It reads the raw filenames and stores them in the filenames array. This array is later used as x-labels in the graph

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
    This function writes HTML files with the graph images.
    Depending upon the number of files, the images are added dynalically to the HTML file.
*/
void writeToHTML(int numberFiles)
{
    // Basic HTML boilerplate Code is written to the file.
    char init_Code[8192] = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"/><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" /><title>PlagCheck Results</title><link rel=\"stylesheet\" href=\"./style.css\" /><style>*{margin: 0;padding: 0;box-sizing: border-box;}h1 {text-align: center;}</style></head><body><h1>Results for Plagiarism Check</h1>";
    // img tags are generated dynamically based on the number of files.
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
    // Content is pasted to the index.html file.
    FILE *fptr = fopen("./TextPlagiarism/index.html", "w");
    fprintf(fptr, "%s", init_Code);
    fclose(fptr);
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

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Invalid Number of Arguments, Please Provide Filenames !!\n");
        exit(1);
    }
    system("mkdir ./TextPlagiarism/Output_Graphs -p"); // Create a directory to store the output graphs
    char filenames[128][128];
    char originalfileName[128][128]; // This Stores the original Filenames to be used as graph labels
    int originalNumberFiles = 0;
    int num_files = 0;
    readFileNameWithoutUpdation(originalfileName, &originalNumberFiles, argv[1]); // Store the raw filenames in the originalfileName array
    readFileNames(filenames, &num_files, argv[1]);                                // Store the updated filenames in the filenames array(updated file names contain the absolute path)
    int n = num_files;
    list word_files[num_files];
    tree bigramTokens[num_files];  // Create an array of BSTs to store the bigrams of all the files
    tree trigramTokens[num_files]; // Create and array of BSTs to store the trigrams of all the files

    // Memory is allocated for the tokens, totalbigrams, totaltrigrams and file_similarityPairs arrays
    // ALlocation through calloc saves loop time for initialization

    int *tokens = (int *)calloc(num_files, sizeof(int));
    int *totalbigrams = (int *)calloc(num_files, sizeof(int));
    int *totaltrigrams = (int *)calloc(num_files, sizeof(int));

    // The file_similarityPairs array is used to store the similarity pairs of all the files.
    Similarity_Pair file_similarityPairs[num_files];

    // This loop iterates through all the files, tokenizes them and stores the tokens.
    // The bigrams and trigrams are then generated and stored in the respective BSTs.
    // file similairty pairs length are also initialized.
    for (int i = 0; i < num_files; i++)
    {
        init_SLL(&word_files[i]);
        tokens[i] = read_file(filenames[i], &word_files[i]);
        word_files[i].len = tokens[i];
        initBST(&bigramTokens[i]);
        initBST(&trigramTokens[i]);
        getBigrams(&bigramTokens[i], word_files[i], &totalbigrams[i]);
        getTrigrams(&trigramTokens[i], word_files[i], &totaltrigrams[i]);
        file_similarityPairs[i].len = 0;
    }

    // This loop iterates through all the tokens generated in files and calculates the similarity between the files.
    for (int i = 0; i < num_files; i++)
    {
        intersection_of_tokens = 0;
        for (int j = i + 1; j < num_files; j++)
        {
            // intersection_of_tokens is used to store the number of common tokens between the files.
            get_intersection_of_tokens(bigramTokens[i], bigramTokens[j]);
            // Jaccard Similarity is calculated for bigrams and trigrams.
            // Formula used is (Intersection of Tokens)/(Total Tokens)
            double bigram_similarity_file1 = getJaccardSimScore(intersection_of_tokens, totalbigrams[i]);
            double bigram_similarity_file2 = getJaccardSimScore(intersection_of_tokens, totalbigrams[j]);
            intersection_of_tokens = 0;
            // Similarly, the intersection of tokens is calculated for trigrams.
            // Formula used is (Intersection of Tokens)/(Total Tokens)
            get_intersection_of_tokens(trigramTokens[i], trigramTokens[j]);
            double trigram_similarity_file1 = getJaccardSimScore(intersection_of_tokens, totaltrigrams[i]);
            double trigram_similarity_file2 = getJaccardSimScore(intersection_of_tokens, totaltrigrams[j]);

            // The similarity score is calculated as the average of the bigram and trigram similarity scores.
            double file_i_to_file_j_similarity = (bigram_similarity_file1 + trigram_similarity_file1) / 2.0;
            int curr_len = file_similarityPairs[i].len;

            strcpy(file_similarityPairs[i].filenames[curr_len], originalfileName[j]);
            // The similarity score is stored in the file_similarityPairs array.
            file_similarityPairs[i].simscore[curr_len] = file_i_to_file_j_similarity;
            file_similarityPairs[i].len++;

            double file_j_to_file_i_similarity = (bigram_similarity_file2 + trigram_similarity_file2) / 2.0;
            curr_len = file_similarityPairs[j].len;

            strcpy(file_similarityPairs[j].filenames[curr_len], originalfileName[i]);
            file_similarityPairs[j].simscore[curr_len] = file_j_to_file_i_similarity;
            file_similarityPairs[j].len++;
        }
        // The BSTs are deleted after the comparison is done.
        // This saves space for the next files.
        destroyTree(&bigramTokens[i]);
        destroyTree(&trigramTokens[i]);
    }
    // Free the allocated memory
    free(tokens);
    free(totalbigrams);
    free(totaltrigrams);
    // Generate the graph for all the files.
    for (int i = 0; i < n; i++)
        generateGraph(originalfileName[i], file_similarityPairs[i].filenames, file_similarityPairs[i].simscore, file_similarityPairs[i].len, i + 1);
    writeToHTML(num_files);
    // Remove the temporary PDF files
    for (int i = 0; i < pdfFileNameSize; i += 1)
    {
        char command[256];
        strcpy(command, "rm ");
        strcat(command, pdfFileNamesOnly[i]);
        system(command);
        system("rm -rf ./TextPlagiarism/Tests");
    }
    printf("index.html is generated in TextPlagiarism folder\n");
    return 0;
}
