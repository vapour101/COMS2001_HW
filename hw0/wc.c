#include <stdio.h>
#include <ctype.h>

void wc(FILE* ofile, FILE* infile, char* inname)
{
}

int main (int argc, char* argv[])
{
    FILE* file;
    file = fopen(argv[1], "r");
    
    if (file == NULL)
    {
        printf("No such file.\n");
        return 1;
    }
    
    int wordCount = 0, lineCount = 0, byteCount = 0;
    fpos_t fileStart;
    fgetpos(file, &fileStart);
    
    char temp[50];
    for (;fscanf(file, "%s", temp) != EOF; wordCount++)
    {}
    
    fsetpos(file, &fileStart);
    char buffer[100];
    size_t num;
    while (num = fread(buffer, 1, 100, file))
    {
        byteCount += num;
        
        for (int i = 0; i < num; i++)
            if (buffer[i] == '\n')
                lineCount++;
            
        if (num < 100)
            break;
    }
    
    fclose(file);
    
    /*printf("Line count: %i\n", lineCount);
    printf("Word count: %i\n", wordCount);
    printf("Byte count: %i\n", byteCount);*/
    
    printf("%i\t%i\t%i\t%s\n", lineCount, wordCount, byteCount, argv[1]);
    
    return 0;
}
