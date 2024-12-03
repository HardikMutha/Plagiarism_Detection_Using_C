#include "./mainheader.h"
#include <dirent.h>
char pdfFileNamesOnly[64][256];
int pdfFileNameSize = 0;

void check_filetypes_and_update_filenames(char *filename, int fileNumber)
{
    FileType ft = getFileType(filename);
    if (ft == 2)
    {
        char newFilename[128] = "";
        strcat(newFilename, "./Tests/PdfTemp");
        newFilename[strlen(newFilename)] = fileNumber + '0';
        newFilename[strlen(newFilename) + 1] = '\0';
        strcat(newFilename, ".txt");
        strcpy(pdfFileNamesOnly[pdfFileNameSize], newFilename);
        pdfFileNameSize++;
        FILE *fptr = fopen(newFilename, "w");
        if (fptr == NULL)
        {
            printf("Error Opening File\n");
            exit(1);
        }
        char *pdf_data = get_pdf_data(filename);
        fprintf(fptr, "%s", pdf_data);
        free(pdf_data);
        strcpy(filename, newFilename);
        fclose(fptr);
        return;
    }
    return;
}

void readFileNames(char filenames[][128], int *num_files, char *dir_name)
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
                char a[128] = "./Tests/";
                char *temp = realpath(strcat(a, dir->d_name), NULL);
                if (temp)
                {
                    strcpy(filenames[*num_files], temp);
                    check_filetypes_and_update_filenames(filenames[*num_files], *num_files);
                    (*num_files)++;
                }
            }
        }
        closedir(d);
    }
    return;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Invalid Number of Arguments, Please Provide Filenames !!\n");
        exit(1);
    }
    char filenames[128][128];
    int num_files = 0;
    readFileNames(filenames, &num_files, argv[1]);
    list word_files[num_files];
    tree bigramTokens[num_files];
    tree trigramTokens[num_files];
    int *tokens = (int *)calloc(num_files, sizeof(int));
    int *totalbigrams = (int *)calloc(num_files, sizeof(int));
    int *totaltrigrams = (int *)calloc(num_files, sizeof(int));

    for (int i = 0; i < num_files; i++)
    {
        init_SLL(&word_files[i]);
        tokens[i] = read_file(filenames[i], &word_files[i]);
        word_files[i].len = tokens[i];
        initBST(&bigramTokens[i]);
        initBST(&trigramTokens[i]);
        getBigrams(&bigramTokens[i], word_files[i], &totalbigrams[i]);
        getTrigrams(&trigramTokens[i], word_files[i], &totaltrigrams[i]);
    }
    for (int i = 0; i < num_files; i++)
    {
        intersection_of_tokens = 0;
        for (int j = i + 1; j < num_files; j++)
        {
            get_intersection_of_tokens(bigramTokens[i], bigramTokens[j]);
            double bigram_similarity_file1 = getJaccardSimScore(intersection_of_tokens, totalbigrams[i]);
            double bigram_similarity_file2 = getJaccardSimScore(intersection_of_tokens, totalbigrams[j]);
            intersection_of_tokens = 0;
            get_intersection_of_tokens(trigramTokens[i], trigramTokens[j]);
            double trigram_similarity_file1 = getJaccardSimScore(intersection_of_tokens, totaltrigrams[i]);
            double trigram_similarity_file2 = getJaccardSimScore(intersection_of_tokens, totaltrigrams[j]);
            double file_i_to_file_j_similarity = (bigram_similarity_file1 + trigram_similarity_file1) / 2.0;
            double file_j_to_file_i_similarity = (bigram_similarity_file2 + trigram_similarity_file2) / 2.0;
            printf("The Similarity %% of %s with respect to %s is %.2lf%%\n", filenames[i], filenames[j], (file_i_to_file_j_similarity * 100));
            printf("The Similarity %% of %s with respect to %s is %.2lf%%\n", filenames[j], filenames[i], (file_j_to_file_i_similarity * 100));
            // printf("%d\n", j);
        }
        destroyTree(&bigramTokens[i]);
        destroyTree(&trigramTokens[i]);
    }
    free(tokens);
    free(totalbigrams);
    free(totaltrigrams);
    for (int i = 0; i < pdfFileNameSize; i += 1)
    {
        char command[256];
        strcpy(command, "rm ");
        strcat(command, pdfFileNamesOnly[i]);
        system(command);
    }
    return 0;
}
