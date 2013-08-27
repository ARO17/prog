/*
 * ex_4-03_calculator_modulus.c
 *
 * KnR
 * Exercice 4-3
 * Given the basic framework, it's straightforward to extend the calculator.
 * Add the modulus ( % ) operator and provisions for negative numbers. 
 *
 * gcc -Wall -o ex_4-03_calculator_modulus ex_4-03_calculator_modulus.c
 *
 */

#include <stdio.h>
#include <stdlib.h>  /* for atof() */

#define MAXOP   100  /* max size of operand or operator */
#define NUMBER  '0'  /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
	switch (type) {
	case NUMBER:
	    printf("push NUMBER on stack\n");
	    push(atof(s));
	    break;
	case '+':
	    printf("push add result on stack\n");
	    push(pop() + pop());
	    break;
	case '*':
	    printf("push * result on stack\n");
	    push(pop() * pop());
	    break;
	case '-':
	    printf("push neg result on stack\n");
	    op2 = pop();
	    push(pop() - op2);
	    break;
	case '/':
	    printf("push / result on stack\n");
	    op2 = pop();
	    if (op2 != 0.0)
		push(pop() / op2);
	    else
		printf("error: zero divisor\n");
	    break;
	case '\n':
	    printf("\t%.8g\n", pop());
	    break;
	default:
	    printf("error: unknown command %s\n", s);
	    break;
	}
    }
    return 0;
}

#define MAXVAL 100  /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    printf("push: sp = %d\n", sp);

    if (sp < MAXVAL)
	val[sp++] = f;
    else
	printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return pop value from stack */
double pop(void)
{
    printf("pop: sp = %d\n", sp);

    if (sp > 0)
	return val[--sp];
    else {
	printf("error: stack empty\n");
	return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
	;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
	return c;       /* not a number */
    i = 0;
    if (isdigit(c))     /* collect integer part */
	while (isdigit(s[++i] = c = getch()))
	    ;
    if (c == '.')       /* collect fraction part */
	while (isdigit(s[++i] = c = getch()))
	    ;
    s[i] = '\0';
    if (c != EOF)
	ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void)  /* get a (possibly pusched-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  /* push character back on input */
{
    if (bufp >= BUFSIZE)
	printf("ungetch: too many characters\n");
    else
	buf[bufp++] = c;
}
