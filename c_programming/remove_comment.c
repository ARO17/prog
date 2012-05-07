/*
 *
 * knr
 *
 * Exercise 1-23. Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments don't nest.
 *
 */

#include <stdio.h>

#define IN 1 /* inside a comment */
#define OUT 0 /* outside a comment */

/* remove comments */
int main()
{
  char c, c2;
  int state = OUT;
  int quote = OUT; /* inside or outside quote */

  while ((c = getchar()) != EOF) {

    if (quote != IN && state == OUT)
      if (c == '"')
	quote = IN;

    if (quote == IN) {
      if (c == '"')
	quote = OUT;
      printf("%c", c);
    } else {
      if(state == OUT) {
	if (c == '/') {
	  if ((c2 = getchar()) == '*')
	    state = IN;
	  else {
	    printf("%c", c);
	    printf("%c", c2);
	  }
	} else {
	  printf("%c", c);
	}
      }
      else {
	while (state != OUT) {
	  if (c == '*') {
	    if ((c2 = getchar()) == '/')
	      state = OUT;
	    else
	      c = c2;
	  } else {
	    c = getchar();
	  }
	}
      }
    }
  }
    
  printf("Just for test purpose : /* comment in quote hehe */\n");

  return /* a difficult to remove comment */ 0;
}
