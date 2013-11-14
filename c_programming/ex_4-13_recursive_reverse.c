/*
 * ex_4-13_recursive_reverse.c -- Ex KnR book
 * 
 * Write a recursive version of the function reverse(s),
 * which reverses the string s in place.
 *
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sat Oct 26 13:46:40 2013 Harold André
 * Last update Sat Oct 26 16:06:36 2013 Harold André
 *
 * gcc -Wall -o ex_4-13_recursive_reverse ex_4-13_recursive_reverse.c
 * 
 */

#include <stdio.h>
#include <string.h>

void reverse(char []);
void reverse2(char []);

int main(void)
{
    char string[] = "voiture";

    printf("Original string: %s\n", string);

    reverse2(string);

    printf("Reversed string: %s\n", string);

    reverse(string);

    printf("Twice reversed string: %s\n", string);

    return 0;
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
    char tmp;
    static int i;

    tmp = s[i];
    s[i] = s[strlen(s) - (i+1)];
    s[strlen(s) - (i+1)] = tmp;

    if((strlen(s) - i) > ((strlen(s) / 2) +1)) {
	i++;
	reverse(s);
    }

    printf("reverse - i: %d, s: %s\n", i, s);

}

/* Sander Goos solution
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_4:Exercise_13
 */
void reverse2(char s[])
{
    static int i, n;
    int c = s[i];

    if (c) {
	i++;
	reverse2(s);
	s[n-i] = c;
	i--;
    } else {
	n = i;
    }

    printf("reverse2 - i: %d, s: %s\n", i, s);
}
