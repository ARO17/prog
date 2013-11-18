/*
 * ex_5-03-06_pointers_characters.c -- Ex KnR book
 * 
 * Ex 5.3
 * Write a pointer version of the function strcat that we showed in Chapter 2:
 * strcat(s,t) copies the string t to the end of s . 
 * Ex 5.4
 * Write the function strend(s,t) , which returns 1 if the string t occurs
 * at the end of the string s , and zero otherwise.
 * Ex 5.5
 * Write versions of the library functions strncpy , strncat , and strncmp,
 * which operate on at most the first n characters of their argument strings.
 * For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B.
 * Ex 5.6
 * Rewrite appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing.
 * Good possibilities include getline (Chapters 1 and 4), atoi, itoa,
 * and their variants (Chapters 2, 3, and 4), reverse (Chapter 3),
 * and strindex and getop (Chapter 4).
 *
 *
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sun Oct 27 00:14:44 2013 Harold André
 * Last update Sat Nov 16 16:12:25 2013 Harold André
 *
 * gcc -Wall -o ex_5-03-06_pointers_characters ex_5-03-06_pointers_characters.c
 *
 * 
 */

#include <stdio.h>

//#define DEBUG

#define SIZE 20

void my_strcat(char *, char*);
int strend(char *, char *);
void my_strncpy(char *, char *, int);
int my_getline(char line[], int max);
int strindex(char source[], char searchfor[]);
void reverse(char s[]);

char pattern[] = "ould"; /* pattern to search for */

int main(void)
{
    char array_src[] = "Salut";
    char array_dest[SIZE] = "yo !";

    char array_1[] = "Salut";
    char array_2[] = "ut";

    char my_strncpy_array_src[] = "Saluttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt";
    char my_strncpy_array_dest[SIZE] = "ut";
    int n = SIZE - 1;

    char line[SIZE];
    int found = 0;
    /*
    my_strcat(array_dest, array_src);
    printf("Concatened string: %s\n", array_dest);

    if (strend(array_1, array_2))
	printf("strend: string 2 occurs at the end of string 1.\n");
    else
	printf("strend: string 2 does not occurs at the end of string 1.\n");

    my_strncpy(my_strncpy_array_dest, my_strncpy_array_src, n);
    printf("my_strncpy copied at max %d characters of string \"%s\": \"%s\"\n", n, my_strncpy_array_src, my_strncpy_array_dest);

    printf("Looking for pattern \"%s\", enter a line, ^D to quit.\n", pattern);
    while (my_getline(line, SIZE) > 0)
	if (strindex(line, pattern) >= 0) {
	    printf("%s", line);
	    found++;
	}
    printf("Number of found patterns: %d\n", found);
    */
    printf("Reverse \"%s\": ", array_src);
    reverse(array_src);
    printf("\"%s\"\n", array_src);

    return 0;
}

/* my_strcat: concatenate src to end of dest; dest must be big enough */
void my_strcat(char *dest, char *src)
{
    while (*dest)
	dest++;
    while (*dest++ = *src++)
	;
}

/* strend: return 1 if string t occurs at the end of s */
int strend(char *s, char *t)
{
    char *start_s = s, *start_t = t;

    while (*s)
	s++;
    while (*t)
	t++;
    /* In answer book, the test is executed only once, is better */
    while (t >= start_t) {
	if (*s != *t || s < start_s)
	    return 0;
	s--;
	t--;
    }
    return 1;
}

void my_strncpy(char *dest, char *src, int n)
{
    int i = 0;

    while (*dest++ = *src++) {
	i++; /* number of copied character */
	if (i == n) {
	    *dest = '\0';
	    break;
	}
    }
}

/* my_getline: get line into s, return length 
   Warning !! The length include the newline
   For exemple: [ line\n\0 ] length is 5 */
int my_getline(char *s, int lim)
{
    int c;
    char *bs = s; /* remember begin of s */

    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
	*s++ = c;
    if (c == '\n')
	*s++ = c;
    *s = '\0';
    printf("my_getline - length of s: %ld\n", (s - bs - 1));
    return (s - bs);
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t)
{
    /*
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++) {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
	    ;
	if (k > 0 && t[k] == '\0')
	    return i;
    }
    */

    char *index_s =  NULL;
    char *bs = s;
    char *bt = t;

    while (*s++) {
	for (index_s = s; *t != '\0' && *index_s == *t; index_s++, t++)
	    ;
	if ((t - bt) > 0 && *t == '\0') {
	    printf("Index of pattern \"%s\" in string \"%s\": %ld\n", bt, bs, s - bs);
	    return s - bs;
	}
    }
    return -1;
}

/* reverse: reverse the string s on itself */
void reverse(char *s)
{
    /*
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    */
    char *bs = s, temp[20] ;

    while (*s++)
	;
    s-=2;
    while (bs < s) {
	*temp = *bs;
	*bs = *s;
	*s = *temp;
	bs++;
	s--;
    }
}
