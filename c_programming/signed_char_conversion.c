/*
 * signed_char_conversion.c -- conversion error with signed char
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Wed Jul 10 20:00:42 2013 Harold André
 * Last update Sat Jul 13 14:29:22 2013 Harold André
 *
 * gcc -Wall -o signed_char_conversion signed_char_conversion.c
 * 
 */

/*
 * when add 1 to 127, c gives -128 and conversion to an unsigned int give
 * -128 + UINT_MAX + 1
 * warning: printf convert arguments too... %u, %d...
 *
 */


#include <stdio.h>

int main(int argc, char *argv[])
{
    char c;

    c = -1;

    do {
	++c;
	printf("c : %u\tc : %u\tc : %u\tc : %d\n", (unsigned int)(unsigned char)c, (unsigned int)c, (unsigned char)c, c);
    }
    while (c + 1 != 0);
    
    return 0;
}
