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
    //int base = HEXADECIMAL_BASE;

    for (i = 0; i <= 20; i++) {
	itob(i, result, base);
	printf("Integer: %d, convert to base %d to string: \"%s\"\n", i, base, result);
    }

    return 0;
}

/* itob: convert int n to base b ascii string s */
void itob(int n, char s[], int b)
{
    int i, r;

    i = 0;

    if ((b != BINARY_BASE) && (b != HEXADECIMAL_BASE)) {
	printf("Convertion to this base unsupported.\n");
	s[i] = '\0';
	return ;
    }

    while (n > 0) {
	r = n;            /* backup n */
	n /= b;
	r = r - (b * n);  /* rest */

	if (r < 10)
	    s[i] = '0' + r;
	else
	    s[i] = 'A' + r - 10;

	i++;
	//printf("n = %d, r = %d, s[%d] = %s\n", n, r, i, s);
    }
    if (i == 0) {
	s[i] = '0';
	i++;
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
