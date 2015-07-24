#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void wc(FILE* ofile, FILE* infile, char* inname)
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
    
    fprintf(ofile, "%i\t%i\t%i\t%s\n", lineCount, wordCount, byteCount, inname);
}

int main (int argc, char* argv[])
{
    FILE* file;
    file = fopen(argv[1], "r");
    
    wc(stdout, file, argv[1]);
    
    fclose(file);
    
    return 0;
}
