/*
 *
 * KnR
 * Exercice 3-2
 * Write a function escape(s,t) that converts characters like newline and tab
 * into visible escape sequences like \n and \t as it copies the string t to s.
 * Use a switch. Write a function for the other direction as well, converting
 * escape sequences into the real characters. 
 *
 */

#include <stdio.h>

#define TAB_SIZE 100

/* escape: convert characters newline and tab into visible escape sequences */
void escape(char s[], char t[]);
/* escape: convert visible escape sequences into characters newline and tab */
void reverse_escape(char s[], char t[]);

int main()
{
  char result[TAB_SIZE];
  //char s[] = "Ligne \tde test\n";
  char s[] = "Ligne \\tde test\\n";

  //escape(s, result);
  reverse_escape(s, result);

  printf("Chaine de base :\n");
  printf("%s\n", s);
  printf("Chaine transformée :\n");
  printf("%s\n", result);

  return 0;
}

/* escape: convert characters newline and tab into visible escape sequences */
void escape(char s[], char t[])
{
  int i = 0;
  int j = 0;
  char c;

  while ((c = s[i]) != '\0') {
    printf("Caractère qui va être traité, position %d : %c\n", i, s[i]);
    switch (c) {
    case '\n':
      t[i+j] = '\\';
      j++;
      t[i+j] = 'n';
      break;
    case '\t':
      t[i+j] = '\\';
      j++;
      t[i+j] = 't';
      break;
    default:
      t[i+j] = s[i];
      break;
    }
    i++;
  }
  t[i+j] = '\0';
}

/* escape: convert visible escape sequences into characters newline and tab */
void reverse_escape(char s[], char t[])
{
  int i = 0;
  int j = 0;
  char c;
  while ((c = s[i]) != '\0') {
    printf("Caractère qui va être traité, position %d : %c\n", i, s[i]);
    switch (c) {
    case '\\':
      if (s[i+1] == 'n') {
	t[i+j] = '\n';
	i++;
	j--;
      } else if (s[i+1] == 't') {
	t[i+j] = '\t';
	i++;
	j--;
      }
      break;
    default:
      t[i+j] = s[i];
      break;
    }
    i++;
  }
  t[i+j] = '\0';
}
