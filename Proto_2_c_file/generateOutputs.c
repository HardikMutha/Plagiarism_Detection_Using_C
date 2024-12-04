#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

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

void generateOutputs(char filenames[][128], int num_files, char *dir_name)
{
    system("mkdir -p ./Outputs/Tests");
    for (int i = 0; i < num_files; i++)
    {
        char temp[256];
        sprintf(temp, "./Outputs/flex_tool ./Proto_2_c_file/Tokenizer/lexical_analyzer_copy.l ./%s/%s", dir_name, filenames[i]);
        system(temp);
        sprintf(temp, "mv output.txt Outputs/Tests/output%d.txt", (i + 1));
        system(temp);
    }
}

int main(int argc, char *argv[])
{
    char *dirName = argv[1];
    char filenames[128][128];
    int num_files = 0;
    readFiles(filenames, &num_files, dirName);
    generateOutputs(filenames, num_files, dirName);
    return 0;
}
