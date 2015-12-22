EXEC = server client

all: $(EXEC)

server: server.c
	gcc -Wall -o $@ $<

client: client.c
	gcc -Wall -o $@ $<

clean:
	rm -rf server client
