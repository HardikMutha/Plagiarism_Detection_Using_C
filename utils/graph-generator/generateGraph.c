#include "../../lib/PbPlots/pbPlots.h"
#include "../../lib/PbPlots/supportLib.h"
void generateGraph(char *parentFile, char childFiles[][128], double *data, int numberofFiles, int filenumber);
BarPlotSettings *mygetUpdatedSettings(wchar_t *barTitle, double *data, int datalen, wchar_t *labels[]);
void intToStr(int N, char *str);

/*
    Function to convert an integer to a string
    This function accepts an integer N and a character array str
    It converts the integer N to a string and stores it in str
*/
void intToStr(int N, char *str)
{
    int i = 0;
    while (N > 0)
    {
        str[i++] = N % 10 + '0';
        N /= 10;
    }
    // Null-terminate the string
    str[i] = '\0';
    // Reverse the string to get the correct order
    for (int j = 0, k = i - 1; j < k; j++, k--)
    {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

/*
    This function generates a graph for the given data and saves it in the Output_Graphs folder
    It takes the following parameters:
        - parentFile: The name of the parent file
        - childFiles: An array of names of the child files
        - data: An array of similarity values
        - numberofFiles: The number of child files
        - filenumber: The number of the file
*/
void generateGraph(char *parentFile, char childFiles[][128], double *data, int numberofFiles, int filenumber)
{
    StartArenaAllocator();
    _Bool success;
    wchar_t *final_filenames[128];
    // Convert the filenames to wide characters
    // Multiply the data by 100 to get the percentage similarity
    for (int i = 0; i < numberofFiles; i++)
    {
        final_filenames[i] = (wchar_t *)malloc(sizeof(wchar_t) * (strlen(childFiles[i]) + 10));
        swprintf(final_filenames[i], 128, L"%hs", childFiles[i]);
        data[i] *= 100;
    }
    wchar_t *finalParentFile = (wchar_t *)malloc(sizeof(wchar_t) * (strlen(parentFile) + 10));
    swprintf(finalParentFile, 128, L"%hs", parentFile); // Convert the parent file to wide characters
    // Get the settings for plotting the graph and draw the graph
    BarPlotSettings *settings = mygetUpdatedSettings(finalParentFile, data, numberofFiles, final_filenames);
    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    StringReference *errorMessage = CreateStringReference(L"", 0);
    success = DrawBarPlotFromSettings(canvasReference, settings, errorMessage);
    // If the graph is successfully drawn, save it to a file
    if (success)
    {
        size_t length;
        ByteArray *pngdata = ConvertToPNG(canvasReference->image); // Convert the image to PNG format
        char temp[128];
        strcpy(temp, "./CPlagiarism/Output_Graphs/");
        strcat(temp, "Graph");
        char x[16];
        intToStr(filenumber, x);
        strcat(temp, x);
        strcat(temp, ".png");
        WriteToFile(pngdata, temp); // write the pngdata to the file (temp)
        DeleteImage(canvasReference->image); // Delete the image from the memory
    }
    else
    {
        // If the graph is not successfully drawn, print the error message
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errorMessage->stringLength; i++)
        {
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }
    // Free the allocated memory
    for (int i = 0; i < numberofFiles; i++)
        free(final_filenames[i]);
    free(finalParentFile);
    FreeAllocations();
}

/*
    This function takes the following parameters:
        - barTitle: The title of the graph
        - data: An array of similarity values
        - datalen: The number of files
        - labels: An array of file names
    Required modifications for the graph are performed here
    The function returns the settings for plotting the graph with the given data
*/
BarPlotSettings *mygetUpdatedSettings(wchar_t *barTitle, double *data, int datalen, wchar_t *labels[])
{
    // Allocate memory for the settings
    BarPlotSettings *settings;
    settings = (BarPlotSettings *)Allocate(sizeof(BarPlotSettings), 1);
    // Settings are modified as the requirements
    settings->width = 800.0;
    settings->height = 800.0;
    settings->autoPadding = false;
    settings->xPadding = 55.0;
    settings->yPadding = 50.0;
    settings->autoBoundaries = false;
    settings->yMax = 100.0;
    settings->yMin = 0.0;
    settings->title = barTitle;

    settings->titleLength = wcslen(settings->title);
    settings->yLabel = L"% similarity ->";
    settings->yLabelLength = wcslen(settings->yLabel);

    settings->barPlotSeries = (BarPlotSeries **)Allocate(sizeof(BarPlotSeries) * (1.0), 1);
    settings->barPlotSeriesLength = 1.0;
    settings->barPlotSeries[0] = GetDefaultBarPlotSeriesSettings();
    Free(settings->barPlotSeries[0]->ys);
    settings->barPlotSeries[0]->ys = data;
    settings->barPlotSeries[0]->ysLength = datalen;

    settings->showGrid = true;
    settings->gridColor = GetGray(0.1);
    settings->autoColor = true;
    settings->autoSpacing = true;
    settings->barSeparation = 0.0;
    settings->groupSeparation = 0.0;

    settings->xLabels = (StringReference **)Allocate(sizeof(StringReference) * (datalen), 1);
    settings->xLabelsLength = datalen;
    settings->autoLabels = false;

    for (int i = 0; i < datalen; i++)
    {
        settings->xLabels[i] = (StringReference *)Allocate(sizeof(StringReference), 1);
        settings->xLabels[i]->string = labels[i];
        settings->xLabels[i]->stringLength = wcslen(settings->xLabels[i]->string);
    }
    settings->barBorder = false;

    return settings;
}
