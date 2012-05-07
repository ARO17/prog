#include <stdio.h>

/* compte les chiffres, les caractères d'espacement et les autres caractères en entrée */

int main() {

  int c, i, nespace, nautre, nmots;
  int nchiffre[10];

  nespace = nautre = 0;
  for (i = 0; i < 10; i++)
    nchiffre[i] = 0;

  while ((c = getchar()) != EOF)
    if (c >= '0' && c <= '9')
      ++nchiffre[c-'0'];
    else if (c == ' ' || c == '\n' || c == '\t')
      ++nespace;
    else
      ++nautre;

  printf("chiffres =");
  for(i = 0; i < 10; i++)
    printf(" %d", nchiffre[i]);
  printf(", espacements = %d, autres = %d\n", nespace, nautre);

  return 0;
}
