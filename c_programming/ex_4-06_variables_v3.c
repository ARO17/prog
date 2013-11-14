/*
 * ex_4-06_variables_v3.c -- Ex KnR book
 *
 * Solution 2 from website
 *
 * Add commands for handling variables.
 * (It's easy to provide twenty-six variables with single-letter names.)
 * Add a variable for the most recently printed value.
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Thu Oct 24 18:34:55 2013 Harold André
 * Last update Thu Oct 24 18:39:33 2013 Harold André
 *
 * gcc -Wall -o ex_4-06_variables_v3 ex_4-06_variables_v3.c -lm
 * 
 */

#include <stdio.h>
#include <stdlib.h>         /* For atof() */
#include <math.h>
#include <ctype.h>

#define MAXOP    100        /* Max size of operand or operator. */
#define NUMBER   '0'        /* Signal that a number was found. */
#define VARIABLE '1'
#define VARMAX   27

int is_first_input = 0;    /* Prevents the solution from being printed on first
                              input */
double var_array[VARMAX];  /* Contains user defined variables. */

int    getop(char []);
void   push(double);
double pop(void);
double top(void);
int    clear(void);
int    swap(void);
int    elem(void);
int    dup(void);
void   sprnt(void);
void   result(void);
void   set_solution(void);
void   print_help(void);

int main()
{
        int type;
        int i, j;
        int op3;
        double topd;
        double op2;
        char s[MAXOP];
        char tmp[MAXOP];

        for (i = 0; i < VARMAX; i++) {
                var_array[i] = 0;
        }

        print_help();

        while ((type = getop(s)) != EOF) {

                op3 = elem();
                if (op3 == 0) { /* Only one input completed. */
                        is_first_input = 1;
                } else if (op3 > 1) {
                        is_first_input = 0;
                }

                i = j = 0;

                switch (type) {
                case NUMBER:
                        push(atof(s));
                        break;
                case VARIABLE:
                        for (i = 2; s[i] != '\0'; i++){
                                tmp[j++] = s[i];
                                tmp[j] = '\0';
                        }
                        var_array[s[0] - 'A'] = atof(tmp);
                        break;
                case '+':
                        push(pop() + pop());
                        break;
                case '*':
                        push(pop() * pop());
                        break;
                case '-':
                        op2 = pop();
                        push(pop() - op2);
                        break;
                case '/':
                        op2 = pop();
                        if (op2 != 0.0){
                                push(pop() / op2);
                        } else {
                                printf("Error: Divide by zero.\n");
                        }
                        break;
                case '%':
                        op3 = (int) pop();
                        push((int) pop() % op3);
                        break;
                case 'c':
                        if (clear()) {
                                printf("Stack Cleared.\n");
                        }
                        break;
                case 'p':
                        if ((topd = top()) != 0) {
                                printf("Top stack element: %g", topd);
                                printf(" of %d elements.\n", elem());
                        }
                        break;
                case 's':
                        if (swap()) {
                                printf("Swap successful.\n");
                        }
                        break;
                case 'd':
                        if (dup()) {
                                printf("Duplication is successful.\n");
                        } else {
                                printf("Error: Stack empty.\n");
                        }
                        break;
                case 'r':
                        sprnt();
                        break;
                case 'o':
                        if (elem() < 2) {
                                printf("Error: pow requires at least two ");
                                printf("items on the stack.\n");
                                break;
                        }
                        op2 = pop();
                        push(pow(op2, pop()));
                        break;
                case 'i':
                        set_solution();
                        push(sin(pop()));
                        result();
                        break;
                case 'y':
                        set_solution();
                        push(cos(pop()));
                        break;
                case 't':
                        set_solution();
                        push(tan(pop()));
                        break;
                case 'x':
                        set_solution();
                        push(exp(pop()));
                        break;
                case 'q':
                        set_solution();
                        push(sqrt(pop()));
                        break;
                case 'f':
                        set_solution();
                        push(floor(pop()));
                        break;
                case 'l':
                        set_solution();
                        push(ceil(pop()));
                        break;
                case 'v':
                        for (i = 0; i < VARMAX; i++) {
                        if (i < VARMAX-1) {
                                printf("%c: %10.10G\n", 'A' + i, var_array[i]);
                        } else {
                                printf("%c: %10.10G\n", '=', var_array[VARMAX]);
                        }
                        }
                        break;
                case 'h':
                        print_help();
                        break;
                case '\n':
                        result();
                        break;
                default:
                        if ((type >= 'A' && type <= 'Z') || type == '=') {
                                if (type != '=') {
                                        push(var_array[type - 'A']);
                                } else {
                                        push(var_array[VARMAX]);
                                }
                        } else {
                                printf("Error: Unknown command \'%s\'\n", s);
                        }
                        break;

                }
        }
        return 0;
}

#define MAXVAL  100     /* Maximum depth of val stack. */
int sp = 0;             /* Next free stack position. */
double val[MAXVAL];     /* Value stack. */

void push(double f)
{
        if (sp < MAXVAL) {
                val[sp++] = f;
        } else {
                printf("Error: Stack full, cannot push %g\n", f);
        }
}

double pop(void)
{
        if (sp > 0) {
                return val[--sp];
        } else {
                printf("Error: Stack empty.\n");
                return 0.0;
        }
}

double top(void)
{
        if (sp > 0) {
                return val[sp-1];
        } else {
                printf("Error: Stack empty.\n");
                return 0.0;
        }
}

int clear(void)
{
        if (sp > 0) {
                while(val[--sp] != '\0');
                sp = 0;
                return 1;
        } else {
                printf("Error: Stack empty.\n");
                return 0;
        }
}

int swap(void)
{
        double sbuf;
        if (sp > 0) {
                sbuf = val[sp-2];
                val[sp-2] = val[sp-1];
                val[sp-1] = sbuf;
                return 1;
        } else {
                printf("Error: Stack empty.\n");
                return 0;
        }
}

int elem(void)
{
        return sp;
}

int dup (void)
{
        if (sp > 0) {
                sp++;
                val[sp] = val[sp-1];
                return 1;
        } else {
                return 0;
        }
}

void sprnt(void)
{
        int count = 0;
        while (count < sp) {
                printf("%d:%10.12g\n", count+1, val[count]);
                count++;
        }
}

void result(void)
{
        if (sp == 1 && is_first_input != 1) {
                printf("Solution: %10.20g\n", val[0]);
                var_array[VARMAX] = val[0];
                is_first_input = 0;
                clear();
        }
}

/*
 * Opens result() for execution.
 * Primarily used with the math functions because they can be used with only
 * one stack item. For ex, if "1 i" is entered as the first input, this
 * function would allow for a result to be shown and the stack cleared.
 */
void set_solution(void)
{
        if (elem() >= 1) {
                is_first_input = 0;
        }
}

int getch(void);
void ungetch(int);

int getop(char s[])
{
        int i = 0, c;
        while ((s[0] = c = getch()) == ' ' || c == '\t');

        s[1] = '\0';

        if (isalpha(c) && c >= 'A' && c <= 'Z') {
                /* Collect the variable. */
                for ( ; s[i] != ' ' && s[i] != '\n'; s[++i] = getch());
                s[i] = '\0';

                if (i > 1) { /* A properly formed variable definition. */
                        return VARIABLE;
                } else {
                        return c;
                }
        } else if (!isdigit(c) && c != '.' && c != '-') {
                return c; /* Not a number. */
        }

        if (c == '-') {
                if ((c = getch()) == ' ') {
                        /* If the next char is space, then c is a operator. */
                        return c;
                } else if (isdigit(c)) {
                        s[++i] = c;
                }

        }

        if (isdigit(c)) { /* Collect integer part. */
                while (isdigit(s[++i] = c = getch()));
        }

        if (c == '.') {   /* Collect fraction part. */
                while (isdigit(s[++i] = c = getch()));
        }

        s[i] = '\0';
        if (c != EOF) {
                ungetch(c);
        }

        return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];      /* Buffer for ungetch. */
int bufp = 0;           /* Next free position in buf. */

int getch(void)
{
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
        if (bufp >= BUFSIZE) {
                printf("Ungetch: Too many characters.\n");
        } else {
                buf[bufp++] = c;
        }
}

void print_help(void)
{
        printf("The Polish Calculator\n");
        printf("-----------------------------------------------\n");
        printf("-> Enter equations in the form: \"1 1 + 2 5 + *\"\n");
        printf("-> Use \"A=1 B=2 C=3\" to store variables.\n");
        printf("-> Use \"A B C * *\" to use stored variables.\n");
        printf("-----------------------------------------------\n");
        printf(">>> Command Help:\n");
        printf(">>>     c:      Clear memory.\n");
        printf(">>>     p:      Print last character.\n");
        printf(">>>     s:      Swap last two characters.\n");
        printf(">>>     d:      Duplicate the last input.\n");
        printf(">>>     r:      Print the entire stack.\n");
        printf(">>>     v:      Print variable list.\n");
        printf(">>>     o:      pow(x,y), x^y, x > 0.\n");
        printf(">>>     i:      sin(x), sine of x.\n");
        printf(">>>     y:      cos(x), cosine of x.\n");
        printf(">>>     t:      tan(x), tangent of x.\n");
        printf(">>>     x:      exp(x), e^x, exponential function.\n");
        printf(">>>     q:      sqrt(x), x >= 0, square of x.\n");
        printf(">>>     f:      floor(x), largest integer not greater than x.\n");
        printf(">>>     l:      ceil(x), smallest integer not less than x.\n");
        printf(">>>     =:      Access the last successful solution.\n");
        printf(">>>     h:      Print this help text.\n");
}
