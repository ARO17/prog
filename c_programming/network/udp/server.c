/*
 * server.c -- UDP server
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Fri Nov 13 19:42:26 2015 Harold André
 * Last update Mon Nov 23 20:17:16 2015 Harold André
 *
 * compile command:
 *
 *     gcc -Wall -o server server.c
 * 
 */

#include <stdio.h>
#include <string.h> // memset
//close
#include <unistd.h>

// inet_aton
#include <arpa/inet.h>
#include <netinet/in.h>

// socket, recv
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 100

int init_addr(struct sockaddr_in *, char *, int);

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in addr;
    struct sockaddr_in src_addr;
    socklen_t len_inet = 0;
    ssize_t read_bytes = 0;
    ssize_t wrote_bytes = 0;
    int data_size = 0;
    char buf[BUFSIZE];

    // create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
	perror("socket");
	return -1;
    }

    // init server address
    if (init_addr(&addr, "127.0.0.1", 1234) < 0) {
	fprintf(stdout, "init_addr error\n");
	return -1;
    }

    // associate socket and address and port
    if (bind(sock, (struct sockaddr *) &addr,
	     sizeof(struct sockaddr_in)) < 0) {
	close(sock);
	perror("bind");
	return -1;
    }

    len_inet = sizeof(src_addr);

    printf("Listen on %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    
    // received data
    for (;;) {
	if ((read_bytes = recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr*) &src_addr, &len_inet)) < 0) {
	    perror("recvfrom");
	    return -1;
	} else {
	    printf("Received from: %s, %d\n", inet_ntoa(src_addr.sin_addr), ntohs(src_addr.sin_port));
	    printf("%d bytes received\nReceived data: %s\n", (int)read_bytes, buf);

	    strcpy(buf, "ack");
	    data_size = strlen(buf) + 1;
	    
	    // send data
	    if ((wrote_bytes = sendto(sock, buf, data_size, 0, (struct sockaddr*) &src_addr, sizeof(struct sockaddr_in))) < 0) {
		perror("sendto");
		return -1;
	    }
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
