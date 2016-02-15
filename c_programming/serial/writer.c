/*
 * writer.c -- Write to serial port
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sun Jan 10 21:38:59 2016 Harold André
 * Last update Sun Jan 10 21:39:19 2016 Harold André
 * 
 */

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <stdlib.h>  /* exit function */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

/* functions declarations  */
int open_port(char *file);

int main(int argc, char **argv)
{
    int fd;
    int n;

    if (argc != 3) {
	printf("usage: %s serial_port_filename message\n", argv[0]);
	exit(-1);
    }

    fd = open_port(argv[1]);

    n = write(fd, argv[2], (strlen(argv[2])));
    if (n < 0) {
	fprintf(stderr, "write() failed\n");
    }

    close(fd);
    
    return 0;
}

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */
int open_port(char *file)
{
    int fd; /* File descriptor for the port */

    fd = open(file, O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (fd == -1) {
	perror("open");
    }
    else {
	fcntl(fd, F_SETFL, 0);
    }

    return (fd);
}
