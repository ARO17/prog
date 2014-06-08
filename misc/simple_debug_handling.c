/*
 * debug_handling.c -- Debug handling macro
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Wed Jun  4 16:27:07 2014 Harold André
 * Last update Wed Jun  4 17:24:46 2014 Harold André
 * 
 * gcc -Wall simple_debug_handling.c -o simple_debug_handling -DDEBUG
 *
 */

#include <stdio.h>
#include <assert.h>

#ifdef DEBUG
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define debug(M, ...)
#endif

/*
#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif
*/

int main(int argc, char *argv[])
{
    int false_value = 0;

    debug("Number of arg: %d", argc);

    /* Used to help programmers find bugs, not for a user */
    /* turned off if NDEBUG is defined */
    assert(false_value);

    return 0;
}
