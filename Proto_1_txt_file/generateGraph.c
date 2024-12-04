/*
    This file contains Various functions required to plot the graph for similarity check result.
*/

#include "../GraphPlot/PbPlots/pbPlots.h"
#include "../GraphPlot/PbPlots/supportLib.h"
void generateGraph(char *parentFile, char childFiles[][128], double *data, int numberofFiles, int filenumber);
BarPlotSettings *mygetUpdatedSettings(wchar_t *barTitle, double *data, int datalen, wchar_t *labels[]);
void intToStr(int N, char *str);

// Coverts an integer to a string.
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
    This function generates the graph for the similarity check result.
    The function takes the following parameters:
        char *parentFile : The name of the parent file
        char childFiles[][128] : The names of the child files
        double *data : The similarity percentage of the child files
        int numberofFiles : The number of child files
        int filenumber : The filenumber of the parent file
    The filenames are of the type char, so they are converted to widechar_t for plotting the graph.


*/

void generateGraph(char *parentFile, char childFiles[][128], double *data, int numberofFiles, int filenumber)
{
    StartArenaAllocator();         // Start the Arena Allocator to start plotting the Graph
    _Bool success;                 // Returns true if the graph was plotted successfully.
    wchar_t *final_filenames[128]; // The filenames in widechar_t format, This will be passed to plotting function.
    for (int i = 0; i < numberofFiles; i++)
    {
        final_filenames[i] = (wchar_t *)malloc(sizeof(wchar_t) * (strlen(childFiles[i]) + 10));
        // Converts the filenames from char to widechar_t
        swprintf(final_filenames[i], 128, L"%hs", childFiles[i]); // This is used to write the filenames in widechar_t format.
        data[i] *= 100;                                           // Mutliply by 100 to get the percentage value.
    }

    // Convert the name of the parent file
    wchar_t *finalParentFile = (wchar_t *)malloc(sizeof(wchar_t) * (strlen(parentFile) + 10));
    swprintf(finalParentFile, 128, L"%hs", parentFile);

    // Get the updated settings for the graph
    BarPlotSettings *settings = mygetUpdatedSettings(finalParentFile, data, numberofFiles, final_filenames);

    // Create a canvas to save the generated image in .png format in Output_Graphs folder
    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();

    // Error Message to be printed if graph plotting fails
    StringReference *errorMessage = CreateStringReference(L"", 0);
    success = DrawBarPlotFromSettings(canvasReference, settings, errorMessage); // Draw the graph
    if (success)
    {
        /*
            If the graph plotting is successfull, convert the canvas to PNG formate using ConvertToPNG function
            Store the pngdata to a file in Output_Graphs folder.
            The file name is determined based on the current file number.
            The Location finally generated would be of the type -  ./Output_Graphs/Graphx.png where x is the file number.
        */
        size_t length;
        ByteArray *pngdata = ConvertToPNG(canvasReference->image);
        char temp[128];
        strcpy(temp, "./Proto_1_txt_file/Output_Graphs/");
        strcat(temp, "Graph");
        char x[16];
        intToStr(filenumber, x);
        strcat(temp, x);
        strcat(temp, ".png");
        WriteToFile(pngdata, temp);
        DeleteImage(canvasReference->image);
    }
    else
    {
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errorMessage->stringLength; i++)
        {
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }
    for (int i = 0; i < numberofFiles; i++)
        free(final_filenames[i]); // Free the allocated memory
    free(finalParentFile);
    FreeAllocations();
}

/*
    This Function returns a structure of BarPlotSettings
    This structure contains all the necessary parameters which are required to plot a bargraph.
    The parameters are:
        widechar_t *barTitle: The title of the graph
        double *data : Data for the barplot
        int datalen : size of the data
        widechar_t *labels[] : x - Labels for the data
    All the property names are self-explainatory
*/

BarPlotSettings *mygetUpdatedSettings(wchar_t *barTitle, double *data, int datalen, wchar_t *labels[])
{
    BarPlotSettings *settings;
    settings = (BarPlotSettings *)Allocate(sizeof(BarPlotSettings), 1);
    settings->width = 1000.0;
    settings->height = 1000.0;
    settings->autoPadding = false;
    settings->xPadding = 80.0;
    settings->yPadding = 80.0;
    settings->autoBoundaries = false;
    settings->yMax = 100.0;
    settings->yMin = 0.0;
    settings->title = barTitle;

    settings->titleLength = wcslen(settings->title);
    settings->yLabel = L"% similarity -->";
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
