/*
 * ex_4-06_variables.c -- Ex KnR book
 *
 * Add commands for handling variables.
 * (It's easy to provide twenty-six variables with single-letter names.)
 * Add a variable for the most recently printed value.
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Thu Oct 24 15:33:18 2013 Harold André
 * Last update Thu Oct 24 18:37:28 2013 Harold André
 *
 * gcc -Wall -o ex_4-06_variables ex_4-06_variables.c -lm
 * 
 */


#include <stdio.h>
#include <stdlib.h> /* for atof() - in K&R, math.h is referenced - this is an anachronism */
#include <math.h> /* for sin(), exp(), pow() */
#include <string.h> /* for strcmp() */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define IDENTIFIER 1
#define VARMAX 26 /* variables from 'A' to 'Z' */

//#define DEBUG

double var_array[VARMAX];

int getop(char []);
void push(double);
double pop(void);
void print(void);
void dup(void);
void swap(void);
void clear(void);
void dealWithName(char []);

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
#ifdef DEBUG
		    printf("NUMBER string = %s, NUMBER convert to float = %f\n",s, atof(s));
#endif
		    push(atof(s));
		    break;
		case IDENTIFIER:
#ifdef DEBUG
		    printf("Operator IDENTIFIER receive\n");
#endif
		    dealWithName(s);
		    break;
		case '+':
#ifdef DEBUG
		    printf("Operator '+' receive\n");
#endif
		    push(pop() + pop());
		    break;
		case '*':
#ifdef DEBUG
		    printf("Operator '*' receive\n");
#endif
		    push(pop() * pop());
		    break;
		case '-':
#ifdef DEBUG
		    printf("Operator '-' receive\n");
#endif
		    op2 = pop();
		    push(pop() - op2);
		    break;
		case '/':
#ifdef DEBUG
		    printf("Operator '/' receive\n");
#endif
		    op2 = pop();
		    if(op2 != 0.0)
			push(pop() / op2);
		    else
			printf("error: zero divisor\n");
		    break;
		case '%':
#ifdef DEBUG
		    printf("Operator '%%' receive\n");
#endif
		    op2 = pop();
		    if(op2 != 0.0)
			/* % don't work with double or float type */
			/* we could use fmod instead */
			push((int)pop() % (int)op2);
		    else
			printf("error: zero divisor\n");
		    break;
		case '\n':
		    /* TODO: No pop if stak is empty ?*/
		    printf("\t%.8g\n", pop());
		    break;
		case 'p':
		    print();
		    break;
		case 'd':
		    dup();
		    break;
		case 's':
		    swap();
		    break;
		case 'c':
		    clear();
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
    if (sp < MAXVAL)
	val[sp++] = f;
    else
	printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
	return val[--sp];
    else
	{
	    printf("error: stack empty\n");
	    return 0.0;
	}
}

/* print: print the top element of the stack without popping */
void print(void)
{
    printf("sp = %d\n", sp);
    if (sp > 0)
	printf("%e, %f, %g\n", val[sp-1], val[sp-1], val[sp-1]);
    else
	printf("Stack empty\n");
}

/* dup: duplicate the top element of the stack */
void dup(void)
{
    if (sp > 0) {
	val[sp] = val[sp-1];
	sp++;
    } else {
	printf("error: stack empty, can't duplicate");
    }
}

/* swap: swap the top two elements of the stack */
void swap(void)
{
    /* TODO: improve it without temp*/
    double temp;

    if (sp > 1) {
	temp = val[sp-1];
	val[sp-1] = val[sp-2];
	val[sp-2] = temp;
    } else {
	printf("error: stack hold less than two elements, can't swap");
    }
}

/* clear: clear the stack */
void clear(void)
{
    sp = 0;
}

/* deal with a string/name this may be either a maths function
   or for future exercices: a variable */
void dealWithName(char s[])
{
    double op2;

    if (0 == strcmp(s, "sin"))
	push(sin(pop()));
    else if (0 == strcmp(s, "exp"))
	push(exp(pop()));
    else if (0 == strcmp(s, "pow")) {
	op2 = pop();
	push(pow(pop(), op2));
    }
    else
	printf("%s is not a supported function.\n", s);
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

    /* variables are 'A' to 'Z' */
    if (isalpha(c) && (c >= 'A' || c <= 'Z')) {
	var_array[c - 'A']
	return VARIABLE;
    }

    if (isalpha(c)) {
	i = 0;
	while (isalpha(s[i++] = c))
	    c = getch();
	s[i - 1] = '\0';
	if (c != EOF)
	    ungetch(c);
	return IDENTIFIER;
    }

    if (!isdigit(c) && c != '.' && c != '-')
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
