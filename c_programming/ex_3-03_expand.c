/*
 *
 * KnR
 * Exercice 3-3
 * Write a function expand(s1,s2) that expands shorthand notations like a-z in
 * the string s1 into the equivalent complete list abc...xyz in s2 .
 * Allow for letters of either case and digits, and be prepared to handle cases
 * like a-b-c and a-z0-9 and -a-z .
 * Arrange that a leading or trailing - is taken literally. 
 *
 */

#include <stdio.h>
#include <ctype.h>

#define TAB_SIZE 100

/* expand: expands shorthand notations like a-z in the string s1 
 * into the equivalent complete list abc...xyz in s2
 */
void expand(char s1[], char s2[]);

int main()
{
    char s[] = "Ligne de test -a-g-m-p-z3-7A-Z0-9- \n";
    char result[TAB_SIZE];

    expand(s, result);

    printf("Chaine de base :\n");
    printf("%s\n", s);
    printf("Chaine transformée :\n");
    printf("%s\n", result);

    return 0;
}

/* expand: expands shorthand notations like a-z in the string s1 
 * into the equivalent complete list abc...xyz in s2
 */
void expand(char s1[], char s2[])
{
    int i = 0;
    int j = 0;
    char c = 0;

    /* while the EOF is not reached  */
    while (s1[i] != '\0') {
	/* if a character or a digit is followed by an '-' */
	if (isalnum(s1[i]) && (s1[i+1] == '-')) {
	    /* the character after the '-' is after in the alphabet  */
	    if (s1[i+2] > s1[i]) {
		for (c = s1[i]; c < s1[i+2]; c++, j++)
		    s2[j] = c;
		i += 2;
	    } else {
		s2[j] = s1[i];
		j++;
		i++;
	    }
	} else {
	    s2[j] = s1[i];
	    j++;
	    i++;
	}
    }

    s2[j] = '\0';
}
