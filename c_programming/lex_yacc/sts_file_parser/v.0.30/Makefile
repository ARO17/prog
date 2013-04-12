CFLAGS = -Wall
LDFLAGS = -lfl -ly

all: sts_parser.y.h main.o sts_parser.l.o sts_parser.y.o
	gcc ${CFLAGS} -o sts_parser main.o sts_parser.y.o sts_parser.l.o ${LDFLAGS}
clean:
	rm -f *.o
	rm -f sts_parser.l.c sts_parser.y.c sts_parser.y.h
	rm -f sts_parser

sts_parser.l.o:	sts_parser.l.c
	gcc -c ${CFLAGS} sts_parser.l.c

sts_parser.y.o:	sts_parser.y.c
	gcc -c ${CFLAGS} sts_parser.y.c

sts_parser.l.c: sts_parser.lex
	flex --yylineno sts_parser.lex ; mv -f lex.yy.c sts_parser.l.c

sts_parser.y.c: sts_parser.y
	bison -y -d sts_parser.y ; mv -f y.tab.c sts_parser.y.c; mv -f y.tab.h sts_parser.y.h

sts_parser.y.h: sts_parser.y
	bison -y -d sts_parser.y ; mv -f y.tab.c sts_parser.y.c; mv -f y.tab.h sts_parser.y.h
