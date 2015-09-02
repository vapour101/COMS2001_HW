#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "parse.h"

/*          Get tokens from a line of characters */
/* Return:  new array of pointers to tokens */
/* Effects: token separators in line are replaced with NULL */
/* Storage: Resulting token array points into original line */

#define TOKseparator " \n:"

int nextTokSpecial(char* chk)
{
    for (; *chk != '\0'; chk++){}
    chk++;
    char* toks = TOKseparator;
    for (char* c = chk; *c != '\0'; c++)
    {
        char* temp = strchr(toks, *c);
        if (temp != NULL)
            return 0;
        else if (*c == '"')
            return 1;
    }
    return 0;
}

tok_t *getToks(char *line)
{
    int i;
    char *c;
  
    tok_t *toks = malloc(MAXTOKS*sizeof(tok_t));
    for (i=0; i<MAXTOKS; i++) toks[i] = NULL;     /* empty token array */

    c = strtok(line,TOKseparator);	 /* Start tokenizer on line */
    int bSpecial = 0;
    for (i=0; c && (i < MAXTOKS); i++)
    {
        toks[i] = c;
        
        if (!bSpecial && nextTokSpecial(c))
        {
            bSpecial = 1;
            c = strtok(NULL, "\"");
            continue;
        }
        else if(bSpecial)
        {
            bSpecial = 0;
            c = strtok(NULL, "\"");
            continue;
        }
        
        c = strtok(NULL,TOKseparator);	/* scan for next token */
    }
  return toks;
}

void freeToks(tok_t *toks) {
  free(toks);
}

void fprintTok(FILE *ofile, tok_t *t) {
  int i;
  for (i=0; i<MAXTOKS && t[i]; i++) {
    fprintf(ofile,"%s ", t[i]);
  }
  fprintf(ofile,"\n");
}

int strCount(char* str, char sub)
{
    int ret = 0;
    
    for (; str[0] != '\0'; str++)
        if (str[0] == sub) ret++;
        
    return ret;
}

/* Locate special processing character */
int isDirectTok(tok_t *t, char *R) {
  int i;
  for (i=0; i<MAXTOKS-1 && t[i]; i++) {
    if (strncmp(t[i],R,1) == 0) return i;
  }
  return -1;
}
