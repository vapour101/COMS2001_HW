#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

void printLine(int lines, int words, int bytes, char* file)
{
    printf("%i\t%i\t%i\t%s\n", lines, words, bytes, file);
}

void wc(FILE* infile, char* inname, int* tLines, int* tWords, int* tBytes)
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
    while (num = fread(buffer, 1, 100, infile))
    {
        byteCount += num;
        
        for (int i = 0; i < num; i++)
            if (buffer[i] == '\n')
                lineCount++;
            
        if (num < 100)
            break;
    }
    
    *tLines += lineCount;
    *tWords += wordCount;
    *tBytes += byteCount;
    
    printLine(lineCount, wordCount, byteCount, inname);
}

int main (int argc, char* argv[])
{
    FILE* file;
    int lines = 0, words = 0, bytes = 0;
    
    for (int i = 1; i < argc; i++)
    {
        file = fopen(argv[i], "r");
        wc(file, argv[i], &lines, &words, &bytes);
        fclose(file);
    }
    
    printLine(lines, words, bytes, "total");
    
    return 0;
}
