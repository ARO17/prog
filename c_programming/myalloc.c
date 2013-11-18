/*
 * myalloc.c -- basic alloc memory library
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Sat Nov 16 15:20:11 2013 Harold André
 * Last update Sat Nov 16 15:27:20 2013 Harold André
 * 
 */

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *myalloc(int n)    /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else      /* not enough room */
        return 0;
}

void myfree(char *p) /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
