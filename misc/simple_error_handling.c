/*
 * error_handling.c -- Error handle example
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Tue Jun  3 12:39:12 2014 Harold André
 * Last update Wed Jun  4 18:17:52 2014 Harold André
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    FILE *fd;
    int errnum;

    if ((fd = fopen("filedoesnotexist.txt", "r")) == NULL) {
	errnum = errno;
	fprintf(stderr, "Value of errno: %d\n", errno);
	fprintf(stderr, "%s, line %u: %s\n", __FILE__, __LINE__, strerror( errnum ));
	fprintf(stderr, "%s, line %u: ", __FILE__, __LINE__);
	/* perror is more portable than strerror */
        perror("fopen");
	exit(EXIT_FAILURE);
    } else {
	fputs("Hello World !", fd);
	fclose(fd);
    }

    //exit(EXIT_SUCCESS);
    return 0;
}
