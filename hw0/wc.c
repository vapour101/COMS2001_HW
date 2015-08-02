#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max(a,b) (a>b?a:b)

void wc(FILE*, char*);
void addLine(int, int, int, char*);
void printLines();

typedef struct{
    int lines;
    int words;
    int bytes;
    char* file;
} Line;

Line* output;
int iOutput;
int maxWidth;

int main (int argc, char* argv[])
{
    if (argc == 1)
        return 0;
    
    maxWidth = 0;
    iOutput = (argc == 2) ? 1 : argc;
    
    FILE* file;
    output = (Line*) malloc(sizeof(Line) * iOutput);
    
    if (iOutput > 1)
    {
        output[iOutput-1].lines = 0;
        output[iOutput-1].words = 0;
        output[iOutput-1].bytes = 0;
        output[iOutput-1].file = "total";
    }
    
    for (int i = 1; i < argc; i++)
    {
        file = fopen(argv[i], "r");
        wc(file, argv[i]);
        fclose(file);
    }
    
    printLines();
    
    return 0;
}

void addLine(int lines, int words, int bytes, char* file)
{
    static int i = 0;
    
    char buffer[50];
    
    sprintf(buffer, "%i", lines);
    maxWidth = max(maxWidth, strlen(buffer));
    
    sprintf(buffer, "%i", words);
    maxWidth = max(maxWidth, strlen(buffer));
    
    sprintf(buffer, "%i", bytes);
    maxWidth = max(maxWidth, strlen(buffer));
    
    output[i].lines = lines;
    output[i].words = words;
    output[i].bytes = bytes;
    output[i].file = file;
    
    i++;
    
    if (iOutput > 1)
    {
        output[iOutput-1].lines += lines;
        output[iOutput-1].words += words;
        output[iOutput-1].bytes += bytes;
    }
}

void printLines()
{
    char outputFormat[256];
    sprintf(outputFormat, "%%%ii %%%ii %%%ii %%s\n", maxWidth, maxWidth, maxWidth);
    
    //printf("DEBUG\n%s\nEND DEBUG\n", outputFormat);
    
    for (int i = 0; i < iOutput; i++)
        printf(outputFormat, output[i].lines, output[i].words, output[i].bytes, output[i].file);
}

void wc(FILE* infile, char* inname)
{
    if (infile == NULL)
    {
        printf("No such file.\n");
        exit(1);
    }
    
    int wordCount = 0, lineCount = 0, byteCount = 0;
    fpos_t fileStart;
    fgetpos(infile, &fileStart);
    
    char temp[50];
    for (;fscanf(infile, "%s", temp) != EOF; wordCount++)
    {}
    
    fsetpos(infile, &fileStart);
    char buffer[100];
    size_t num;
    while ((num = fread(buffer, 1, 100, infile)))
    {
        byteCount += num;
        
        for (int i = 0; i < num; i++)
            if (buffer[i] == '\n')
                lineCount++;
            
        if (num < 100)
            break;
    }
    
    addLine(lineCount, wordCount, byteCount, inname);
}
