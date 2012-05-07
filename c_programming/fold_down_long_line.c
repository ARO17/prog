/*
 *
 * knr ex 1.22
 *
 */

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */
#define CUTCOLUMN 10 /* column before fold down the line */

int krgetline(char line[], int maxline);
int slen(char string[]);
void folddownline(char string[], int cutcolumn);
void copy(char to[], char from[]);

/* print the longest input line */
int main()
{
  int len; /* current line length */
  //  int max; /* maximum length seen so far */
  char line[MAXLINE]; /* current input line */
  //char longest[MAXLINE]; /* longest line saved here */

  while ((len = krgetline(line, MAXLINE)) > 0)
    if (len > CUTCOLUMN) {
      folddownline(line, CUTCOLUMN);
      printf("%s\n", line);
    }

  return 0;
}

/* krgetline: read a line into s, return length */
int krgetline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

/* slen: return lentgh of s */
int slen(char s[])
{
  int i = 0;

  while (s[i] != '\0')
    i++;

  return i;
}

/* folddownline: fold down line */
void folddownline(char s[], int lim)
{
  int i, j, lastBlankCaracterPos;

  i = j = 0;
  lastBlankCaracterPos = -1;

  printf("length of string: %d\n", slen(s));

  while (i < slen(s)) {

    if (s[i] == ' ' || s[i] == '\t')
      lastBlankCaracterPos = i;

    if (j == lim) {

      if (lastBlankCaracterPos != -1) {
	s[lastBlankCaracterPos] = '\n'; /* fold down the line */
	lastBlankCaracterPos = -1;
      }
      else 
	;//s[i] = '\n';
      j = 0;

    }
    i++;
    j++;
  }
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
