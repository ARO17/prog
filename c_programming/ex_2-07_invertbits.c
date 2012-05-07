/*
 *
 * KnR
 * Exercice 2-7
 * Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted
 * (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. 
 *
 */

#include <stdio.h>
#include <string.h>

/* invertbits: returns x with the n bits that begin at position p
   invert, 1 become 0 */
unsigned invertbits(unsigned x, int p, int n);
/* dtob: convert decimal < 256 to binary string */
void dtob(int x, char *result);

int main()
{
  char binary_str[] = "xxxxxxxx";
  unsigned x = 127;
  unsigned y = 12;
  unsigned k = 0;
  int p = 4;
  int n = 3;

  k = setbits(x, p, n, y);
  printf("setbits(%u, %d, %d, %u) = %u\n", x, p, n, y, k);

  dtob(x, binary_str);
  printf("x: %s\n", binary_str);

  dtob(y, binary_str);
  printf("y: %s\n", binary_str);

  dtob(k, binary_str);
  printf("k: %s\n", binary_str);

  return 0;
}

/* invertbits: returns x with the n bits that begin at position p
   invert, 1 become 0 */
unsigned invertbits(unsigned x, int p, int n)
{
  
}

/* dtob: convert decimal < 256 to binary string */
void dtob(int x, char *result)
{
  int i, bit_number;
  
  bit_number = 7;

  for (i = 0; i < strlen(result); i++)
    result[i] = '0';

  while (x > 0) {
    if (x % 2)
      result[bit_number--] = '1'; 
    else
      result[bit_number--] = '0'; 
    x >>= 1; /* divise par 2 */
  }
}
