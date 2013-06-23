/*
 * ex_4-02_atof.c
 *
 * KnR
 * Exercice 4-1
 * Write the function strrindex(s,t) , which returns the position of the
 * rightmost occurrence of t in s , or -1 if there is none.
 *
 * gcc -Wall -o ex_4-02_atof ex_4-02_atof.c
 *
 */

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

double atof(char s[]);
int atoi(char s[]);
int mygetline(char line[], int max);

/* rudimentary calculator */
int main()
{
    double sum, atof(char []);
    char line[MAXLINE];
    int mygetline(char line[], int max);

    sum = 0;
    while (mygetline(line, MAXLINE) > 0)
	printf("\t%g\n", sum += atof(line));
    return 0;
}

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power, power_val;
    int i, sign;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
	;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
	i++;
    for (val = 0.0; isdigit(s[i]); i++)
	val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
	i++;
    for (power = 1.0; isdigit(s[i]); i++) {
	val = 10.0 * val + (s[i] - '0');
	power *= 10;
    }
    if (s[i] == 'e' || s[i] == 'E') {
	i++;
	val = sign * val / power; /* get number value */
	sign = 0;
	sign = (s[i] == '-') ? 1 : 0; /* manage exponent sign */
	if (s[i] == '+' || s[i] == '-')
	    i++;
	for (power = 0.0; isdigit(s[i]); i++) { /* get power value */
	    power = 10.0 * power + (s[i] - '0');
	}
	for (power_val = val; power > 1; power--)
	    val *= power_val;
	if (sign)
	    return 1 / val;
	return val;
    }
    return sign * val / power;
}

/* atoi: convert string s to integer using atof */
int atoi(char s[])
{
    double atof(char s[]);

    return (int) atof(s);
}

/* mygetline: get line into s, return length */
int mygetline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
	s[i++] = c;
    if (c == '\n')
	s[i++] = c;
    s[i] = '\0';
    return i;
}
