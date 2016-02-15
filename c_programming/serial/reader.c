/*
 * reader.c -- Read from serial port
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sat Jan  9 14:50:00 2016 Harold André
 * Last update Tue Jan 26 21:45:11 2016 Harold André
 * 
 */

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <stdlib.h>  /* exit and malloc function */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/ioctl.h> /* ioctl function */

/* functions declarations  */
int open_port(char *file);

int main(int argc, char **argv)
{
    int fd = 0;
    int bytes_to_read = 0;
    int bytes_read = 0;
    int bytes_count = 0;
    char *buf = NULL;
    int i = 0;
    char c;

    if (argc != 2) {
	printf("usage: %s serial_port_filename\n", argv[0]);
	exit(-1);
    }

    if ((buf = malloc(sizeof(*buf))) == NULL) {
	fprintf(stderr, "malloc fail");
	exit(-1);
    }

    fd = open_port(argv[1]);

    bytes_to_read = 6;

    while (1) {
	/* gets the number of bytes in the serial port input buffer */
	ioctl(fd, FIONREAD, &bytes_to_read);
	if (bytes_to_read > 0) {
	    printf("There is %d bytes available, do you want read it ? (y or n)\n", bytes_to_read);
	    if ((c = getchar()) == 'y') {
		printf("DEBUG - %c", c);
		while (bytes_read < bytes_to_read) {
		    /* read data from serial port */
		    if ((bytes_count = read(fd, (void *)(buf + bytes_read), bytes_to_read)) == -1) {
			perror("read");
			close(fd);
			exit(-1);
		    } else {
			bytes_read += bytes_count;
		    }
		}
		/* display data read */
		for (i = 0; i < bytes_read; i++) {
		    putchar(buf[i]);
		}
		bytes_read = 0;
	    }
	    printf("DEBUG - %c", c);
	}
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
