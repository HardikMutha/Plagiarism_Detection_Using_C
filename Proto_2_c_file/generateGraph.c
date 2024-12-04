#include "../GraphPlot/PbPlots/pbPlots.h"
#include "../GraphPlot/PbPlots/supportLib.h"
void generateGraph(char *parentFile, char childFiles[][64], double *data, int numberofFiles, int filenumber);
BarPlotSettings *mygetUpdatedSettings(wchar_t *barTitle, double *data, int datalen, wchar_t *labels[]);
void intToStr(int N, char *str);

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

void generateGraph(char *parentFile, char childFiles[][64], double *data, int numberofFiles, int filenumber)
{
    StartArenaAllocator();
    _Bool success;
    wchar_t *final_filenames[128];
    for (int i = 0; i < numberofFiles; i++)
    {
        final_filenames[i] = (wchar_t *)malloc(sizeof(wchar_t) * (strlen(childFiles[i]) + 10));
        swprintf(final_filenames[i], 128, L"%hs", childFiles[i]);
        data[i] *= 100;
    }
    wchar_t *finalParentFile = (wchar_t *)malloc(sizeof(wchar_t) * (strlen(parentFile) + 10));
    swprintf(finalParentFile, 128, L"%hs", parentFile);
    BarPlotSettings *settings = mygetUpdatedSettings(finalParentFile, data, numberofFiles, final_filenames);
    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    StringReference *errorMessage = CreateStringReference(L"", 0);
    success = DrawBarPlotFromSettings(canvasReference, settings, errorMessage);
    if (success)
    {
        size_t length;
        ByteArray *pngdata = ConvertToPNG(canvasReference->image);
        char temp[128];
        strcpy(temp, "./Proto_2_c_file/Output_Graphs/");
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
        free(final_filenames[i]);
    free(finalParentFile);
    FreeAllocations();
}

BarPlotSettings *mygetUpdatedSettings(wchar_t *barTitle, double *data, int datalen, wchar_t *labels[])
{
    BarPlotSettings *settings;
    settings = (BarPlotSettings *)Allocate(sizeof(BarPlotSettings), 1);
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
