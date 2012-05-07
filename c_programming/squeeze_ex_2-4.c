/*
 *
 * KnR
 * 
 * Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes each character in
 * s1 that matches any character in the string s2.
 *
 */

#include <stdio.h>

#define MAXLINE 20

void squeeze(char s1[], char s2[]);

int main()
{
  char str[MAXLINE] = "harold";
  char mask[MAXLINE] = "hrd";

  squeeze(str, mask);

  printf("%s\n", str);

  return 0;
}

/* squeeze: delete each character in s1 
   that matches any character in the string s2 */
void squeeze(char s1[], char s2[])
{
  int i, j, k, match;

  match = 0;

  i = 0;

  /* while (match == 0) { */
  /*   if (s1[i] == 'o') */
  /*     match = 1; */
  /*   printf("%c\n", s1[i++]); */
  /* } */

  for (i = k = 0; s1[i] != '\0'; i++) {

    for (j = 0; match == 0 && s2[j] != '\0' ; j++)
      if (s1[i] == s2[j])
  	match = 1;

    if (match == 0) {
      s1[k++] = s1[i];
    }
    match = 0;

    printf("s1: %s, s2: %s\n", s1, s2);
  }

  s1[k] = '\0';
}
