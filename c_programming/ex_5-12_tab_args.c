/*
 * ex_5-12_tab_args.c -- Ex KnR book
 *
 * Exercise 5-12. Extend entab and detab to accept the shorthand
 *   entab -m +n
 * to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behavior.
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Tue Jun 17 20:14:36 2014 Harold André
 * Last update Tue Jun 17 20:54:40 2014 Harold André
 * 
 * gcc -Wall -g -o ex_5-12_tab_args ex_5-12_tab_args.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE  100   /* maximum line size */
#define TABINC   8     /* default tab increment size */
#define YES      1
#define NO       0

void esettab(int argc, char *argv[], char *tab);
void entab(char *tab);
void detab(char *tab);
int tabpos(int pos, char *tab);

/* replace strings of blanks with tabs */
int main(int argc, char *argv[])
{
    char tab[MAXLINE+1];

    esettab(argc, argv, tab); /* initialize tab stops */
    entab(tab); /* replace blanks with tabs */
    detab(tab); /* replace tab with blanks */

    return 0;
}

/* entab: replace strings of blanks with tabs and blanks */
void entab(char *tab)
{
    int c, pos;
    int nb = 0; /* # of blanks necessary */
    int nt = 0; /* # of tabs necessary */

    for (pos = 1; (c = getchar()) != EOF; pos++) {
	if (c == ' ') {
	    if (tabpos(pos, tab) == NO) {
		++nb; /* increment # of blanks */
	    } else {
		nb = 0; /* reset # of blanks */
		++nt; /* one more tab */
	    }
	} else {
	    for ( ; nt > 0; nt--) {
		putchar('\t'); /* output tab(s) */
	    }
	    if (c == '\t') { /* forget the blank(s) */
		nb = 0;
	    } else { /* output blank(s) */
		for ( ; nb > 0; nb--) {
		    putchar(' ');
		}
	    }	
	    putchar(c);
	    if (c == '\n') {
		pos = 0;
	    } else if (c == '\t') {
		while (tabpos(pos, tab) != YES) {
		    ++pos;
		}
	    }
	}
    }
}

/* detab: replace tab with blanks */
void detab(char *tab)
{
    int c, pos = 1;

    while ((c = getchar()) != EOF) {
	if (c == '\t') { /* tab character */
	    do {
		putchar(' ');
	    } while (tabpos(pos++, tab) != YES);
	} else if (c == '\n') { /* newline character */
	    putchar(c);
	    pos = 1;
	} else { /* all other characters */
	    putchar(c);
	    ++pos;
	}
    }
}

/* esettab: set tab stops in array tab */
void esettab(int argc, char *argv[], char *tab)
{
    int i, inc, pos;

    printf("In esettab function\n");

    if (argc <= 1) { /* default tab stops */
	for (i = 1; i <= MAXLINE; i++) {
	    if (i % TABINC == 0) {
		tab[i] = YES;
	    } else {
		tab[i] = NO;
	    }
	}
    } else if (argc == 3 && /* user provided range */
	       *argv[1] == '-' && *argv[2] == '+') { 
	pos = atoi(((*++argv)+1));
	inc = atoi(&(*++argv)[1]);

	printf("pos: %d, inc: %d\n", pos, inc);

	for (i = 1; i <= MAXLINE; i++) {
	    if (i != pos) {
		tab[i] = NO;
	    } else {
		tab[i] = YES;
		pos += inc;
	    }
	}
    } else { /* user provided tab stops */
	for (i = 0; i <= MAXLINE; i++) {
	    tab[i] = NO; /* tune off all tab stops */
	}
	while (--argc > 0) { /* walk through argument list */
	    pos = atoi(*++argv);
	    if (pos > 0 && pos <= MAXLINE) {
		tab[pos] = YES;
	    }
	}
    }
}

/* tabpos: determine if pos is at a tab stop */
int tabpos(int pos, char *tab)
{
    if (pos > MAXLINE) {
	return YES;
    } else {
	return tab[pos];
    }
}
