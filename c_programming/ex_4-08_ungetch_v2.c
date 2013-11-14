/*
 * ex_4-08_ungetch_v2.c -- Ex KnR book
 *
 * Suppose that there will never be more than one character of pushback.
 * Modify getch and ungetch accordingly.
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Fri Oct 25 14:19:52 2013 Harold André
 * Last update Fri Oct 25 14:39:56 2013 Harold André
 *
 * gcc -Wall -o ex_4-08_ungetch_v2 ex_4-08_ungetch_v2.c -lm
 * 
 */


#include <string.h>
#include <stdio.h>

int getch(void);
void ungetch(int);
 
int main(void)
{
  char *s = "hello, world.  this is a test.";
  int c;
  int i = 0;

  while (s[i] != '\0')
      ungetch(s[i++]);

  while ((c = getch()) != EOF)
    putchar(c);               

  return 0;
}


int buf = -1; /* the unget char */

int getch(void) /* get a (possibly pushed back) character */
{
    int tmp = -1;

    if (buf != -1) {
	tmp = buf;
	buf = -1;
    }

    return (tmp != -1) ? tmp : getchar();
}

void ungetch(int c) /* push character back on input */
{
    buf = c;
}
