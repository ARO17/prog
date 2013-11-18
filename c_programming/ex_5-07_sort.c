/*
 * ex_5-07_sort.c -- Ex KnR book
 * 
 * Rewrite readlines to store lines in an array supplied by main, rather than
 * calling alloc to maintain storage. How much faster is the program?
 *
 *
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sat Nov 16 14:55:54 2013 Harold André
 * Last update Sat Nov 16 21:15:03 2013 Harold André
 *
 * gcc -Wall -o ex_5-07_sort ex_5-07_sort.c mygetline.c myalloc.c
 *
 * 
 */


#include <stdio.h>
#include <string.h>

#define MAXLINES 500     /* max #lines to be sorted */
#define ALLOCSIZE 1000

char *lineptr[MAXLINES];  /* pointers to text lines */
char allocbuf[ALLOCSIZE];

int readlines_v1(char *lineptr[], int nlines);
int readlines_v2(char *lineptr[], char *buf, int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
    int nlines;     /* number of input lines read */

    if ((nlines = readlines_v2(lineptr, allocbuf, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 100 /* max length of any input line */

int mygetline(char *, int);
char *myalloc(int);

/* readlines_v1: read input lines */
int readlines_v1(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = myalloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */ /* ERROR */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* readlines_v2: read input lines */
int readlines_v2(char *lineptr[], char *buf, int maxlines)
{
    int len, nlines;
    char line[MAXLEN];
    char *p = buf;
    char *maxbuf = p + ALLOCSIZE; 

    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p + len > maxbuf)
            return -1;
        else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
	    p += len;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) /* do nothing if array contains */
        return;         /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
  for (i = left+1; i <= right; i++)
      if (strcmp(v[i], v[left]) < 0)
          swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
