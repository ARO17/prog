/*
 *
 * KnR
 * Exercice 3-4
 * In a two's complement number representation, our version of itoa does not
 * handle the largest negative number, that is, the value of n equal to 
 * -(2 to the power (wordsize - 1)) . Explain why not. Modify it to print that
 * value correctly regardless of the machine on which it runs.
 *
 * gcc -Wall -o ex_3-04_itoa ex_3-04_itoa.c
 *
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define TAB_SIZE 100

/* itoa: convert int n to ascii string s */
void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
    int i = pow(2, 31)*-1;
    char result[TAB_SIZE];

    itoa(i, result);

    printf("INT_MIN: %d\n", INT_MIN);
    printf("Integer: %d, convert to string: \"%s\"\n", i, result);

    return 0;
}

/* itoa: convert int n to ascii string s */
void itoa(int n, char s[])
{
    int i, signe;

    if ((signe = n) <0)    /* backup the sign */
	n = -n;            /* make n positive */
    printf("signe = %d\n", signe);
    printf("n = %d\n", n);
    i = 0;
    do {                        /* extract digit in revese order */
	s[i++] = n%10 + '0';    /* read the next digit */
	printf("%d%%10 : %d\n", n, n%10);
    } while ((n /= 10) > 0);    /* then delete */
    if (signe < 0)
	s[i++] = '-';
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
