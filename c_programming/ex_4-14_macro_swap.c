/*
 * ex_4-14_macro_swap.c -- Ex KnR book
 * 
 * Define a macro swap(t,x,y) that interchanges two arguments of type t.
 * (Block structure will help.)
 *
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sun Oct 27 00:14:44 2013 Harold André
 * Last update Sun Oct 27 00:50:45 2013 Harold André
 *
 * gcc -Wall -o ex_4-14_macro_swap ex_4-14_macro_swap.c
 *
 * See the result after preprocess only:
 * gcc -Wall -E ex_4-14_macro_swap.c -o ex_4-14_macro_swap.i
 * 
 */

#include <stdio.h>

#define swap(t,x,y) { t _z;   \
	              _z = x; \
		      x = y;  \
		      y = _z; }


int main(void)
{
    int i = 12;
    int j = 68;

    {
	int i = 8;
	printf("i = %d\n", i);
	{
	    int i = 34;
	    printf("i = %d\n", i);
	}
    }

    printf("Before swap: i = %d, j = %d\n", i, j);

    swap(int, i, j);

    printf("After swap: i = %d, j = %d\n", i, j);

    return 0;
}
