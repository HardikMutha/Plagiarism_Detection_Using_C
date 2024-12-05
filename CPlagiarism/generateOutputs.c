#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/*
    This function takes an array of filenames, integer to store the number of files
    and a directory name as input
    In the function, directory is opened and all the filenames are updated in the array
    The number of files is also updated
*/
void readFiles(char filenames[][128], int *num_files, char *dir_name)
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
                strcpy(filenames[*num_files], dir->d_name);
                (*num_files)++;
            }
        }
        closedir(d);
    }
}

/*
    This function takes an array of filenames, number of files and a directory name as input
    The function generates the output of the tokenizer for all the files in the directory
    The output files are stored in the Outputs/Tests directory
*/
void generateOutputs(char filenames[][128], int num_files, char *dir_name)
{
    system("mkdir -p ./Outputs/Tests");
    for (int i = 0; i < num_files; i++)
    {
        char temp[256];
        sprintf(temp, "./Outputs/flex_tool ./CPlagiarism/Tokenizer/lexical_analyzer.l ./%s/%s", dir_name, filenames[i]);
        system(temp);
        sprintf(temp, "mv output.txt Outputs/Tests/output%d.txt", (i + 1));
        system(temp);
    }
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Invalid Number of Arguments\n");
        return -1;
    }
    char *dirName = argv[1];
    char filenames[128][128];
    int num_files = 0;
    readFiles(filenames, &num_files, dirName);
    generateOutputs(filenames, num_files, dirName);
    return 0;
}
