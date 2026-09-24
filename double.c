#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "misc.h"

int getword(FILE *fp, char *buf, size_t size);
void doubleword(const char* word, FILE *fp);

int main(int argc, char *argv[])
{
  int i;
  for(i = 1; i < argc; ++i)
    {
      FILE *fp = fopen(atgv[i], "r");
      if(fp == NULL)
	{
	  fprintf(stderr, "%s: can't open '%s' (%s)\n",
		   argv[0], argv[i], strerror(errno));
	  return(1);
	}
      doubleword(argv[i], fp);
      fclose(fp);
    }
  if(argc == 1) doubleword(NULL, stdin);
  return(0);
}

int getword(FILE *fp, char *buf, size_t size)
{
  int c = getc(fp);
  // scan forward to a nonspace character or EOF
  // copy the word into buf
  if(c != EOF) ungetc(c, fp);
  // return exit_failure in case of bad luck?
  return(0);
}

void doubleword(const char* word, FILE *fp)
{

}
