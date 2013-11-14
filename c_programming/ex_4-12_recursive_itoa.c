/*
 * ex_4-12_recursive_itoa.c -- Ex KnR book
 * 
 * Adapt the ideas of printd to write a recursive version of itoa;
 * that is, convert an integer into a string by calling a recursive routine.
 *
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sat Oct 26 12:47:50 2013 Harold André
 * Last update Sat Oct 26 14:10:05 2013 Harold André
 *
 * gcc -Wall -o ex_4-12_recursive_itoa ex_4-12_recursive_itoa.c
 * 
 */


#include <stdio.h>

#define MAXCHAR 100
char ascii_int[MAXCHAR];

/* printd: print n in decimal */
void printd(int);
/* itoa: convert integer to string */
void itoa(int, char []);

int main(void)
{
    int i = 12345678;

    printd(i);

    itoa(i, ascii_int);

    printf("\nitoa: decimal: %d -> string: %s\n", i, ascii_int);

    i = 987;

    itoa(i, ascii_int);

    printf("\nitoa: decimal: %d -> string: %s\n", i, ascii_int);
    
    return 0;
}

/* printd: print n in decimal */
void printd(int n)
{
    if (n < 0) {
	putchar('-');
	n = -n;
    }
    if (n / 10)
	printd(n / 10);
    putchar(n % 10 + '0');
}

void itoa(int n, char s[])
{
    static int i; /* static variable is initialized with 0 by convention */

    if (n < 0) {
	s[i++] = '-';
	n = -n;
    }
    
    if (n / 10)
	itoa(n / 10, s);
    else
	i = 0;
    s[i++] = (n % 10 + '0');

    s[i] = '\0';
}
