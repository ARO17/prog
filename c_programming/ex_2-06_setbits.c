/*
 *
 * KnR
 * Exercice 2-6
 * Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p
 * set to the rightmost n bits of y, leaving the other bits unchanged. 
 *
 */

#include <stdio.h>
#include <string.h>

/* setbits: returns x with the n bits that begin at position p
   set to the rightmost n bits of y */
unsigned setbits(unsigned x, int p, int n,unsigned y);
/* readbits: return n bits that begin at position p */
unsigned readbits(unsigned x, int p, int n);
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

/* setbits: returns x with the n bits that begin at position p
   set to the rightmost n bits of y */
unsigned setbits(unsigned x, int p, int n,unsigned y)
{
  return (x & ((~0 << (p + 1)) | (~(~0 << (p + 1 - n))))) | ((y & ~(~0 << n)) << (p + 1 - n));
}

/* readbits: return n bits that begin at position p */
unsigned readbits(unsigned x, int p, int n)
{
  return (x >> (p+1-n)) & ~(~0 << n);
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
