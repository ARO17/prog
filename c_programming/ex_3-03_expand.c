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

#define TAB_SIZE 100

/* expand: expands shorthand notations like a-z in the string s1 
 * into the equivalent complete list abc...xyz in s2
 */
void expand(char s1[], char s2[]);

int main()
{
  char s[] = "Ligne \\tde test\\n";
  char result[TAB_SIZE];

  escape(result, s);

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

  while (s1[i] != '\0') {
    
  }
}
