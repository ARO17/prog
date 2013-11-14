/*
 * ex_4-09_ungetch_EOF.c -- Ex KnR book
 *
 * Our getch and ungetch do not handle a pushed-back EOF correctly.
 * Decide what their properties ought to be if an EOF is pushed back,
 * then implement your design.
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Fri Oct 25 14:41:47 2013 Harold André
 * Last update Fri Oct 25 17:34:53 2013 Harold André
 *
 * gcc -Wall -o ex_4-09_ungetch_EOF ex_4-09_ungetch_EOF.c -lm
 * 
 */


#include <string.h>
#include <stdio.h>

int getch(void);
void ungetch(int);
 
int main(void)
{
    //  char *s = "hello, world.  this is a test.";
  int c;
  //int i = 0;

  //while (s[i] != '\0')
  //  ungetch(s[i++]);

  while ((c = getch()))
    putchar(c);               

  return 0;
}

#define BUFSIZE 100

/* use int type for buf array to handle EOF
 * Because EOF is frequently -1 and convesion to char result to 1 */
int buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if(bufp >= BUFSIZE)
	printf("ungetch: too many characters\n");
    else
	buf[bufp++] = c;
}
