/*
 * client.c -- UDP client
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Fri Nov 13 19:42:59 2015 Harold André
 * Last update Mon Nov 23 20:15:13 2015 Harold André
 *
 * compile command:
 *
 *     gcc -Wall -o client client.c
 * 
 */

#include <stdio.h>
// strncpy
#include <string.h>
//close
#include <unistd.h>

// inet_aton
#include <arpa/inet.h>

// sockaddr_in
#include <netinet/in.h>

// socket, sendto
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 100

int init_addr(struct sockaddr_in *, char *, int);

int main(int argc, char *argv[])
{
    int sock = 0;
    struct sockaddr_in server_addr;
    struct sockaddr_in my_addr;
    ssize_t wrote_bytes = 0;
    ssize_t read_bytes = 0;
    int data_size = 0;
    char buf[BUFSIZE] = {0};

    data_size = strlen(argv[1]) + 1;
    
    if (data_size > BUFSIZE) {
	printf("Error, too long string");
	return -1;
    } else {
	strncpy(buf, argv[1], data_size);
    }

    // create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
	perror("socket");
	return -1;
    }

    // init my address
    if (init_addr(&my_addr, "192.168.1.136", 8765) < 0) {
	fprintf(stdout, "init_addr error\n");
	return -1;
    }

    // associate my(sender/client) socket and address and port
    if (bind(sock, (struct sockaddr *) &my_addr,
	     sizeof(struct sockaddr_in)) < 0) {
	close(sock);
	perror("bind");
	return -1;
    }

    // init server address
    if (init_addr(&server_addr, "127.0.0.1", 1234) < 0) {
	fprintf(stdout, "init_addr error\n");
	return -1;
    }

    printf("Send on %s:%d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));
    printf("Listen on %s:%d\n", inet_ntoa(my_addr.sin_addr), ntohs(my_addr.sin_port));

    // send data
    if ((wrote_bytes = sendto(sock, buf, data_size, 0, (struct sockaddr*) &server_addr, sizeof(struct sockaddr_in))) < 0) {
	perror("sendto");
	return -1;
    } else {
	printf("%d bytes sended\nSended data: %s\n", (int)wrote_bytes, buf);

	// received data
	if ((read_bytes = recv(sock, buf, BUFSIZE, 0)) < 0) {
	    perror("recv");
	    return -1;
	} else {
	    printf("%d bytes received\nReceived data: %s\n", (int)read_bytes, buf);
	}
    }
    
    return 0;
}

int init_addr(struct sockaddr_in *addr, char *ip, int port)
{
    // init sockaddr structure
    memset(addr, 0, sizeof (struct sockaddr_in));

    // set family
    addr->sin_family = AF_INET;

    // set port
    addr->sin_port = htons(port);

    // set address
    if (inet_aton(ip, &addr->sin_addr) == 0) {
	fprintf(stdout, "bad address: %s\n", ip);
	return -1;
    }
    
    return 0;
}
