
#include <stdio.h>
#include <string.h>

/* Convert decimal < 256 to binary string */
void dtob(int x, char *result);

int main()
{
  int i = 118;
  int j = 0;
  char binary_str[] = "88888888";

  printf("sizeof(char) = %lu\n", sizeof(char));
  printf("sizeof(short) = %lu\n", sizeof(short));
  printf("sizeof(int) = %lu\n", sizeof(int));
  printf("sizeof(signed int) = %lu\n", sizeof(signed int));
  printf("sizeof(unsigned int) = %lu\n", sizeof(unsigned int));
  printf("sizeof(float) = %lu\n", sizeof(float));
  printf("sizeof(double) = %lu\n", sizeof(double));

  dtob(i, binary_str);

  printf("%d to binary : %s\n", i, binary_str);

  j = ~i;

  printf("i = %d(%x)(%o), j = %d(%x)(%o)\n", i, i, i, j, j, j);

  return 0;
}

/* Convert decimal < 256 to binary string */
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

#ifdef NOTDEF
/* Convert char to binary string */
char *ctob(int i)
{
  int dividende, diviseur, quotient, reste, bit_number;
  char binary[9] = {'0', '0', '0', '0', '0', '0', '0', '0'};
  //char binary[] = "00000000";

  dividende = i;
  diviseur = 2;
  quotient = i;
  reste = -1;
  bit_number = 7;

  while (quotient > 0) {
    quotient = dividende / diviseur;
    reste = dividende % diviseur;
    if (reste == 1)
      binary[bit_number] = '1';
    bit_number -= 1;
    dividende = quotient;
  }
  
  //  while (quotient > 0) {
  //    dividende >>= 1; /* divise par 2 */
    
  return binary;
}
#endif
