/*
 *
 * KnR
 * 
 * Exercise 2-3. Write a function htoi(s), which converts a string of hexadecimal digits
 * (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
 * through 9, a through f, and A through F.
 *
 */

#include <stdio.h>
#include <ctype.h>

int htoi(char s[]);

int main()
{
  int decimal = 442;
  int octal = 0672;
  int hexa = 0x1bA;
  char hexa_str[] = "0x1bA";

  printf("decimal : %d, %d, %d\n", decimal, octal, hexa);
  printf("octal : %o, %o, %o\n", decimal, octal, hexa);
  printf("hexadecimal : %x, %x, %x\n", decimal, octal, hexa);

  printf("hexadecimal \"%s\" convert with my htoi function to decimal = %d\n", hexa_str, htoi(hexa_str));

  return 0;
}

/* convert hexadecimal string into integer */
int htoi(char s[])
{
  int i, hexa_start, n;

  i = hexa_start = n = 0;

  if(s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    hexa_start = 2;

  for (i = hexa_start; isxdigit(s[i]); i++) {
    if (isdigit(s[i]))
      n = 16 * n + (s[i] - '0');
    else if (isupper(s[i]))
      n = 16 * n + (s[i] - 'A') + 10;
    else if (islower(s[i]))
      n = 16 * n + (s[i] - 'a') + 10;
  }

  return n;
}
