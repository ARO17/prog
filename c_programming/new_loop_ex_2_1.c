/*
 *
 * KnR
 * 
 * for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 *     s[i] = c;
 *
 * Exercise 2-2. Write a loop equivalent to the for loop above without using && or ||.
 *
 */

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int krgetline(char line[], int maxline);
void copy(char to[], char from[]);

/* print input line */
int main()
{
  int len; /* current line length */
  char line[MAXLINE]; /* current input line */
  char linecopy[MAXLINE];


  while ((len = krgetline(line, MAXLINE)) > 0) {
    copy(linecopy, line);
    printf("%s", linecopy);
  }

  return 0;
}

/* krgetline: read a line into s, return length */
int krgetline(char s[],int lim)
{
  int c, i;

  /*  for (i=0; i < lim-1 && (c=getchar())!=EOF && c != '\n'; ++i) */
  i = 0;
  while (i < lim-1) {
    printf("while 1\n");
    while ((c=getchar())!=EOF) {
      printf("while 2\n");
      while (c != '\n') {
	printf("while 3\n");
	s[i] = c;
      }
    }
    i++;
  }
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
