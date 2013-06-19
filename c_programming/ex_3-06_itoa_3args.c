/*
 * ex_3-06_itoa_3args.c
 *
 * KnR
 * Exercice 3-6
 * Write a version of itoa that accepts three arguments instead of two.
 * The third argument is a minimum field width; the converted number must be
 * padded with blanks on the left if necessary to make it wide enough. 
 *
 * gcc -Wall -o ex_3-06_itoa_3args ex_3-06_itoa_3args.c
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>


/* itoa: convert int n to ascii string s with width w*/
void itoa(int n, char s[], int width);
/* reverse: reverse the string s on itself */
void reverse(char s[]);


int main(void) {
    char buffer[20];
    
    printf("INT_MIN: %d\n", INT_MIN);
    itoa(INT_MIN, buffer, 20);
    printf("Buffer : %s\n", buffer);
    
    return 0;
}

void itoa(int n, char s[], int width) {
    int i, sign;
    sign = n;
    
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ( n /= 10 );
    if (sign < 0)
        s[i++] = '-';

    while (i < width )    /*  Only addition to original function  */
        s[i++] = ' ';
    
    s[i] = '\0';
    reverse(s);
}

/* reverse: reverse the string s on itself */
void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
