/*
 * ex_3-05_itob.c
 *
 * KnR
 * Exercice 3-5
 * Write the function itob(n,s,b) that converts the integer n into a base b
 * character representation in the string s . In particular, itob(n,s,16)
 * formats n as a hexadecimal integer in s.
 *
 * gcc -Wall -o ex_3-05_itob ex_3-05_itob.c
 *
 */

#include <stdio.h>
#include <string.h>

#define TAB_SIZE 100
#define BINARY_BASE 2
#define HEXADECIMAL_BASE 16

/* itob: convert int n to base b ascii string s */
void itob(int n, char s[], int b);
/* reverse: reverse the string s on itself */
void reverse(char s[]);


int main()
{
    int i;
    char result[TAB_SIZE];
    int base = BINARY_BASE;

    for (i = 0; i <= 10; i++) {
	itob(i, result, base);
	printf("Integer: %d, convert to base %d to string: \"%s\"\n", i, base, result);
    }

    return 0;
}

/* itob: convert int n to bas b ascii string s */
void itob(int n, char s[], int b)
{
    int i, r;

    i = 0;

    while (n > 0) {
	r = n;
	n /= 2;
	r = r - (2 * n);
	if (r == 1)
	    s[i] = '1';
	else
	    s[i] = '0';
	i++;
	//printf("n = %d, r = %d, s[%d] = %s\n", n, r, i, s);
    }
    s[i] = '\0';

    reverse(s);
}

/* reverse: reverse the string s on itself */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
	c = s[i];
	s[i] = s[j];
	s[j] = c;
    }
}
