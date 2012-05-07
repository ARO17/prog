/* gcc -g -Wall -L/usr/X11R6/lib -lX11 demo_graphics.c -o demo_graphics */

#include<X11/Xlib.h>
#include<stdio.h>
#include<X11/Xutil.h>
#include<math.h>
#include <stdlib.h>

#define Hauteur 600
#define Largeur 600
#define XMAX 600
#define YMAX 600

int pix[XMAX][YMAX];

Display *d; /* le serveur */
Window W; /* la fenetre pere */
GC gc; /* les contexe graphique */
XFontStruct *fd; /* la police */
XGCValues gcv;

void init();
void createWindow();
void draw();

void createWindow()
{
  if((d=XOpenDisplay(getenv("DISPLAY")))==NULL)
    {
      fprintf(stderr,"Impossible de contacter le serveur %s \n",getenv("DISPLAY"));
      exit(1);
    }

  W=XCreateSimpleWindow(d,RootWindow(d,DefaultScreen(d)),0,0,600,600,2
			,BlackPixel(d,DefaultScreen(d)),
			WhitePixel(d,DefaultScreen(d)));

  if((fd=XLoadQueryFont(d,"fixed"))==NULL)
    {
      fprintf(stderr,"impossible de charger la police fixed \n");
      exit(1);
    }

  /* le contexe gc */
  gcv.font=fd->fid;
  gcv.foreground=BlackPixel(d,DefaultScreen(d));
  gc=XCreateGC(d,W,GCFont | GCForeground,&gcv);

  /* l'affichage de la fenetre principale */
  XMapWindow(d,W);
  XSelectInput(d,W,ExposureMask );
  XStoreName(d,W,"My first graphic demo ;)");
}

void init()
{
  int j, k;

  for (j = 0;j < Hauteur;j++)
    {
      for (k = 0;k < Largeur;k++)
	pix[j][k] = 0;
    }
}


void draw()
{
  int x0 = 100, y0 = 100;
  int x1 = 200, y1 = 200;
  int i;
  
  //  XDrawPoint(d, W, gc, x0, y0);
  
  /* Dessiner les lignes joignants les quatres points */
  for (i = 0; i <= 100; i++) {
    XDrawLine(d, W, gc, x0 + i * 2, y0 + i * 2, x1 + i, y1 + i);
  }
  XDrawLine(d, W, gc, 24,  560, 23, 40);
}

int main(int argc, char **argv)
{

#ifdef NOTDEF
  if (argc != 9)
    {
      fprintf(stderr, "Usage : %s x0 y0 x1 y1 x2 y2 x3 y3.\n", argv[0]);
      exit(0);
    }
#endif

  init();
  createWindow();

  for (;;)
    {
      XEvent e;
      XNextEvent(d,&e);
      switch(e.type)
	{
	default:
	  break;

	case Expose:
	  /* Appeller la fonction de dessin */
	  draw();

	  break;
	}
    }

  return 0;
}

