/*
 * ex_4-03_modulus.c -- Ex KnR book
 *
 * Given the basic framework, it's straightforward to extend the calculator.
 * Add the modulus ( % ) operator and provisions for negative numbers.
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Mon Jul 22 10:24:18 2013 Harold André
 * Last update Wed Jul 24 13:14:27 2013 Harold André
 *
 * gcc -Wall -o ex_4-03_modulus ex_4-03_modulus.c
 * 
 */


#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF)
	{
	    switch(type)
		{
		case NUMBER:
		    printf("NUMBER string = %s, NUMBER convert to float = %f\n",s, atof(s));
		    push(atof(s));
		    break;
		case '+':
		    printf("Operator '+' receive\n");
		    push(pop() + pop());
		    break;
		case '*':
		    printf("Operator '*' receive\n");
		    push(pop() * pop());
		    break;
		case '-':
		    printf("Operator '-' receive\n");
		    op2 = pop();
		    push(pop() - op2);
		    break;
		case '/':
		    printf("Operator '/' receive\n");
		    op2 = pop();
		    if(op2 != 0.0)
			push(pop() / op2);
		    else
			printf("error: zero divisor\n");
		    break;
		case '%':
		    printf("Operator '%%' receive\n");
		    op2 = pop();
		    if(op2 != 0.0)
			/* % don't work with double or float type */
			/* we could use fmod instead */
			push((int)pop() % (int)op2);
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

#define MAXVAL  100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if(sp < MAXVAL)
	val[sp++] = f;
    else
	printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if(sp > 0)
	return val[--sp];
    else
	{
	    printf("error: stack empty\n");
	    return 0.0;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    /* ignore space and tabulation characters */
    while((s[0] = c = getch()) == ' ' || c == '\t')
	;

    s[1] = '\0'; /* useless ??? why this line, avoid security whole ? */

    if(!isdigit(c) && c != '.' && c != '-')
	return c; /* not a number */

    i = 0;
    /* a minus immediatly follow by a number is a negative number
       otherwise is minus operator */
    if (s[0] == '-') {
	c = getch();
	if (!isdigit(c) && c != '.') {
	    if(c != EOF)
		ungetch(c);
	    return s[0];
	} else {
	    s[++i] = c;
	}
    }

    if(isdigit(c)) /* collect integer part */
	while(isdigit(s[++i] = c = getch()))
	    ;
    if(c == '.') /* collect fraction part */
	while(isdigit(s[++i] = c = getch()))
	    ;
    s[i] = '\0';
    if(c != EOF)
	ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
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
