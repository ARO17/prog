/*
 * ex_5-10_expr.c -- Ex KnR book
 * 
 * Exercise 5-10. Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is
 * a separate argument. For example,
 *  expr 2 3 4 + *
 * evaluates 2 * (3+4).
 *
 *
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Mon Nov 25 16:39:33 2013 Harold André
 * Last update Tue Nov 26 13:48:33 2013 Harold André
 *
 * gcc -Wall -g -o ex_5-10_expr ex_5-10_expr.c
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>  /* for atof() */

#define MAXOP   100  /* max size of operand or operator */
#define NUMBER  '0'  /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */

#define DEBUG

double val[MAXVAL]; /* value stack */
double *sp = val;         /* next free stack position */

/* push: push f onto value stack */
void push(double f)
{
#ifdef DEBUG
    printf("push: sp = %f\n", *sp);
#endif

    if (sp - val < MAXVAL)
	*sp++ = f;
    else
	printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return pop value from stack */
double pop(void)
{
#ifdef DEBUG
    printf("pop: sp = %f\n", *sp);
#endif

    if (sp - val > 0)
	return *--sp;
    else {
	printf("error: stack empty\n");
	return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char *s)
{

    if (!isdigit(*s) && *s != '.')
	return *s;       /* not a number */
    if (isdigit(*s))     /* collect integer part */
	while (isdigit(*++s))
	    ;
    if (*s == '.')       /* collect fraction part */
	while (isdigit(*++s))
	    ;
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
char *bufp = buf;       /* next free position in buf */

int getch(void)  /* get a (possibly pusched-back) character */
{
    return (bufp - buf > 0) ? *--bufp : getchar();
}

void ungetch(int c)  /* push character back on input */
{
    if (bufp - buf >= BUFSIZE)
	printf("ungetch: too many characters\n");
    else
	*bufp++ = c;
}

/* reverse Polish calculator */
int main(int argc, char *argv[])
{
    int type;
    double op2;
    
    /*
      int i, j;
    for (i = 0; i < argc; i++) {
	printf("Command line argument: %s\n", argv[i]);
	for (j = 0; argv[i][j] != '\0'; j++)
	    printf("\tcharacters of command line argument: %c\n", argv[i][j]);
    }
    */
    /*
    while (--argc > 0 && ++argv != NULL) {
	printf("Command line argument: %s\n", *argv);
	while (*argv[0] != '\0')
	    printf("\tcharacters of command line argument: %c\n", *argv[0]++);
    }
    */
    /*
    while (--argc > 0 && ++argv != NULL) {
	printf("Command line argument: %s\n", *argv);
	while (**argv != '\0')
	    printf("\tcharacters of command line argument: %c\n", *(*argv)++);
    }
    */
    
    while (--argc > 0 && ++argv != NULL) {
	type = getop(*argv);
	switch (type) {
	case NUMBER:
#ifdef DEBUG
	    printf("push NUMBER on stack\n");
#endif
	    push(atof(*argv));
	    break;
	case '+':
#ifdef DEBUG
	    printf("push add result on stack\n");
#endif
	    push(pop() + pop());
	    break;
	case '*':
#ifdef DEBUG
	    printf("push * result on stack\n");
#endif
	    push(pop() * pop());
	    break;
	case '-':
#ifdef DEBUG
	    printf("push neg result on stack\n");
#endif
	    op2 = pop();
	    push(pop() - op2);
	    break;
	case '/':
#ifdef DEBUG
	    printf("push / result on stack\n");
#endif
	    op2 = pop();
	    if (op2 != 0.0)
		push(pop() / op2);
	    else
		printf("error: zero divisor\n");
	    break;
	default:
	    printf("error: unknown command %s\n", *argv);
	    break;
	}
    }
    printf("\t%.8g\n", pop());

    return 0;
}
