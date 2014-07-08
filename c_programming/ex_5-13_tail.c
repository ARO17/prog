/*
 * ex_5-13_tail.c -- Ex KnR book
 * 
 * Exercise 5-13. Write the program tail, which prints the last n lines
 * of its input. By default, n is set to 10, let us say, but it can be changed
 * by an optional argument so that
 *  tail -n
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or the value of n. Write the program so it makes
 * the best use of available storage; lines should be stored as in the sorting
 * program of Section 5.6, not in a two-dimensional array of fixed size.
 *
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Wed Jun 18 00:41:03 2014 Harold André
 * Last update Sat Jul  5 15:30:01 2014 Harold André
 *
 * gcc -Wall -g -o ex_5-13_tail ex_5-13_tail.c
 * 
 */

/*
 * Allocate n pointers to array of character strings
 * Get lines on stdin until EOF
 * Print the last n lines in FIFO order.
 *
 * drawback: We have to read entirely the file...
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_N 10
#define MAX_N 100
#define MAX_INPUT 1000
#define LINES_LENGTH 5000

static void usage(const char *s)
{
    fprintf(stderr, "Usage: %s -n number_of_line\n", s);
    exit(-1);
}

int main(int argc, char *argv[])
{
    int n;
    int i;
    int j;
    int line_length = LINES_LENGTH;
    char **lines;

    if (argc == 1) {
	n = DEFAULT_N;
    } else if (argc == 3) {
	if ((*(argv[1]) != '-') || (*(argv[1] + 1) != 'n'))
	    usage(argv[0]);
	else
	    if ((n = atoi(argv[2])) > MAX_N)
		usage(argv[0]);
    } else {
	usage(argv[0]);
    }

    if ((lines = malloc(n * sizeof (*lines))) == NULL) {
	perror("malloc");
	exit(-1);
    }
    for (i = 0; i < n; i++)
	if ((lines[i] = malloc(LINES_LENGTH * sizeof (*lines[i]))) == NULL) {
	    perror("malloc");
	    exit(-1);
	}

#ifdef NOTDEF
    i = 0;
    while (getline(&lines[i++], (size_t *)&line_length, stdin) > 0) {
	if (i >= n)
	    i = 0;
	//	printf("%d\n", i);
    }

    //    printf("%d\n", i);
    i--;

    for (j = 0; j < n; j++) {
	//	printf("i = %d, j = %d\n", i, j);
	printf("%s", lines[i++]);
	if (i >= n)
	    i = 0;
    }
#endif

    i = 0;
    while (getline(lines + i, (size_t *)&line_length, stdin) > 0) {
	i++;
	if (i >= n)
	    i = 0;
	//	printf("%d\n", i);
    }

    

    for (j = 0; j < n; j++) {
	if (i >= n)
	    i = 0;
	printf("%s", *(lines + i++));
    }

    return 0;
}
