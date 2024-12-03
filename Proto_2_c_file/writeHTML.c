#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeToHTML(int numberFiles);
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
    FILE *fptr = fopen("./index.html", "w");
    fprintf(fptr, "%s", init_Code);
    fclose(fptr);
    return;
}
