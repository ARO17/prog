/*
 * ex_5-01-02_pointers-arrays.c -- Ex KnR book
 * 
 * Ex 5.1
 * As written, getint treats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on the input.
 * Ex 5.2
 * Write getfloat , the floating-point analog of getint.
 * What type does getfloat return as its function value?
 *
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sun Oct 27 00:14:44 2013 Harold André
 * Last update Sun Nov 10 12:27:56 2013 Harold André
 *
 * gcc -Wall -o ex_5-01-02_pointers-arrays ex_5-01-02_pointers-arrays.c
 *
 * 
 */

#include <stdio.h>
#include <ctype.h>

//#define DEBUG

#define SIZE 10

int getch(void);
void ungetch(int);
int getint(int *);
int getfloat(float *);

int main(void)
{
    int n;
    /* int array[SIZE], intrvalue; */
    float floatarray[SIZE], floatrvalue;
    /*
    for (n = 0; n < SIZE && (intrvalue = getint(&array[n])) != EOF; n++)
	printf("Integer from input: %d, return value: %d\n", array[n], intrvalue);
    */
    for (n = 0; n < SIZE && (floatrvalue = getfloat(&floatarray[n])) != EOF; n++)
	printf("Float from input: %g, return value: %f\n", floatarray[n], floatrvalue);

    return 0;
}

#define BUFSIZE 100

/* use int type for buf array to handle EOF
 * Because EOF is frequently -1 and convesion to char result to 1 */
int buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
#if defined(DEBUG)
    int c;

    if (bufp > 0)
	c = buf[--bufp];
    else
	c = getchar();

    printf("DEBUG: getch - Character read: '%c', ascii value: %d\n", c, c);

    return c;
#endif
#if !defined(DEBUG)
    return (bufp > 0) ? buf[--bufp] : getchar();
#endif
}

void ungetch(int c) /* push character back on input */
{
    if(bufp >= BUFSIZE)
	printf("ungetch: too many characters\n");
    else
	buf[bufp++] = c;
#ifdef DEBUG
    printf("DEBUG: ungetch - Push back character: '%c', ascii value: %d\n", c, c);
#endif
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) /* skip white space */
	;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
	ungetch(c); /* it is not a number */
	return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
	c = getch();
	if (!isdigit(c)) {
	    ungetch((sign == -1) ? '-' : '+');
	    return 0;
	}
    }
    for (*pn = 0; isdigit(c); c = getch())
	*pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
	ungetch(c);
    return c;
}

/* getfloat: get next float from input into *pn */
int getfloat(float *pn)
{
    int c, sign, power;

    while (isspace(c = getch())) /* skip white space */
	;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
	ungetch(c); /* it is not a number */
	return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
	c = getch();
	if (!isdigit(c)) {
	    ungetch((sign == -1) ? '-' : '+');
	    return 0;
	}
    }
    for (*pn = 0.0; isdigit(c); c = getch())
	*pn = 10.0 * *pn + (c - '0');
    if (c == '.')
	c = getch();
    for (power = 1; isdigit(c); c = getch()) {
	*pn = 10.0 * *pn + (c - '0');
	power *= 10;
    }
    *pn = sign * *pn / power;
    if (c != EOF)
	ungetch(c);
    return c;
}
