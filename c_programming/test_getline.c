/*
 * test_getline.c -- Simple test of getline function
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Sat Nov 16 16:03:28 2013 Harold André
 * Last update Sat Nov 16 16:07:54 2013 Harold André
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int bytes_read;
  size_t nbytes = 100;
  char *my_string;

  puts ("Please enter a line of text.");

  /* These 2 lines are the heart of the program. */
  my_string = (char *) malloc(nbytes + 1);
  bytes_read = getline(&my_string, &nbytes, stdin);

  if (bytes_read == -1)
    {
      puts ("ERROR!");
    }
  else
    {
      puts ("You typed:");
      puts (my_string);
      printf("string length: %d\n", bytes_read);
    }

  return 0;
}
