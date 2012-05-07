/*
 *
 * Simple example of multidimensional array
 *
 */

#include <stdio.h>

int main()
{
  int i, j;
  int array[3][2];

  for (i = 0; i < 3; i++)
    for (j = 0; j < 2; j++)
      array[i][j] = i+j;

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++)
      printf("[%d]", array[i][j]);
    printf("\n");
  }

  return 0;
}
