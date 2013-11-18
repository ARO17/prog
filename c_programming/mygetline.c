/*
 * mygetline.c -- mygetline library
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Sat Nov 16 15:22:06 2013 Harold André
 * Last update Sat Nov 16 16:16:26 2013 Harold André
 * 
 */

#include <stdio.h>

//#define DEBUG

/* mygetline: get line into s, return length */
int mygetline(char *s, int lim)
{
    int c;
    char *bs = s; /* remember begin of s */

    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
	*s++ = c;
    if (c == '\n')
	*s++ = c;
    *s = '\0';
#ifdef DEBUG
    printf("my_getline - length of s: %d\n", (s - bs));
#endif
    return (s - bs);
}
