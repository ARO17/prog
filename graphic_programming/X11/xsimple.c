/* 
 * xsimple : Affiche une chaine dans une fenetre X...
 * gcc -Wall xsimple.c -o xsimple -lX11
 * ou avec Imakefile :
 *    "xmkmf" pour générer le Makefile à partir de l´Imakefile
 *    "make depend" pour générer les dépendances des fichiers à la fin du Makefile
 *    "make all" oou "make" pour compiler le programme 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <X11/Xlib.h>

GC	gc;
Display	*display;
int	screen;
Window	window, root;
unsigned long white_pixel, black_pixel;

/*
 * fonction associee a l'evenement EXPOSE 
 */

void expose ()
{
  XDrawString (display, window, gc, 10, 30, "Hello, world !", 14);
}

/*
 * programme principal
 */

int main(int ac, char **av)
{
  char *dpyn = NULL;

  /* selection du display en ligne */
  if (ac == 3) {
    if (strcmp (&av[1][1], "display") == 0) {
      dpyn = av[2];
    }
    else {
      fprintf (stderr, "Usage:	xsimple [-display display_name]\n");
      exit (1);
    }
  }

  if ((display = XOpenDisplay (dpyn)) == NULL) {
    fprintf(stderr, "Can't open Display\n");
    exit(1);
  }

  gc = DefaultGC(display, screen);
  screen = DefaultScreen(display);
  root = RootWindow(display, screen);
  white_pixel = WhitePixel(display, screen);
  black_pixel = BlackPixel(display, screen);

  window = XCreateSimpleWindow(display, root, 0, 0, 100, 90, 2, black_pixel, white_pixel);

  XSelectInput(display, window, ExposureMask);

  XStoreName(display, window, "xsimple");
  XMapWindow(display, window);

  for (;;) {
    XEvent xev;
    Window wid;

    XNextEvent(display, &xev);

    switch (xev.type) {

    case Expose :
      expose();
      break;

    case DestroyNotify:
      wid = xev.xdestroywindow.window;
      printf("Window %X destroyed\n", wid);
      if (wid == window) {
	XCloseDisplay(display);
      	exit(0);
      }
      break;

    default :

      break;
	    
    }
  }

  return 0;
}
