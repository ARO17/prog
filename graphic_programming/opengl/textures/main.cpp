/*
 * main.cpp
 *
 */

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include "sdlglutils.h"

using namespace std;

#define FPS 50
#define LARGEUR_FENETRE 320
#define HAUTEUR_FENETRE 240

void dessinerCaisse();
void dessinerPyramide();
void dessinerCaisseBois();
void DrawGL();
void dessinerRepere(unsigned int echelle);

#define VITESSE_MOUVEMENT_CAMERA 0.01
#define VITESSE_ROTATION_PYRAMIDE 0.1
#define VITESSE_DEPLACEMENT_CUBE 0.05
//#define VITESSE_DEPLACEMENT_CAISSE 0.05

double angle_camera = 0;
double angle_pyramide = 0;
double angle_cube = 180;
double x_cube = 2;
//double x_caisse = 2;
double hauteur = 3;

// Les identifiants de texture.
// Vous pouvez utiliser un tableau, je reste comme ça pour être cohérent
// avec les exemples du chapitre
GLuint texture1;
GLuint texture2;
GLuint texture3;
GLuint texture4;

int main()
{
  SDL_Surface *ecran = NULL;
  SDL_Event event;
  const Uint32 time_per_frame = 1000/FPS;

  Uint32 last_time,current_time,elapsed_time; //for time animation
  Uint32 start_time,stop_time; //for frame limit

  // initialisation de la SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      cerr << "Echec SDL_Init : " << SDL_GetError() << endl;
      return (EXIT_FAILURE);
    }
  
  // SDL initialisee, on active la procedure de sortie en fin de programme
  atexit(SDL_Quit);

  // titre de la fenêtre
  SDL_WM_SetCaption("Scene avec textures !!! ;)", NULL);

  // assurons nous que le mode "double buffer" est bien demande
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // activation de l'affichage SDL en mode fenetre
  ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_OPENGL);

  // verification de l'activation de l'affichage
  if( !ecran )
    {
      cerr << "Echec de creation de la fenetre en " << LARGEUR_FENETRE << "x" << HAUTEUR_FENETRE << " : " << SDL_GetError() << endl;
      return (EXIT_FAILURE);
    }

  // recuperation de l'etat du parametre "double buffer"
  int nValue;
  if( SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &nValue) < 0)
    {
      cerr << "Echec de recuperation du parametre SDL_GL_DOUBLEBUFFER : " << SDL_GetError() << endl;
      return (EXIT_FAILURE);
    }

  // assurons nous que le mode "double buffer" est bien actif
  if(nValue != 1)
    {
      cerr << "Erreur : SDL_GL_DOUBLEBUFFER inactif" << endl;
      return (EXIT_FAILURE);
    }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70,(double)LARGEUR_FENETRE/HAUTEUR_FENETRE,1,1000);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  texture1 = loadTexture("stainedglass05.jpg");
  texture2 = loadTexture("tiles_ctf05r.jpg");
  texture3 = loadTexture("caisse.jpg");
  texture4 = loadTexture("metal091.jpg");

  last_time = SDL_GetTicks();
  for (;;)
    {

      start_time = SDL_GetTicks();

      while(SDL_PollEvent(&event))
        {
	  switch(event.type)
            {
	    case SDL_QUIT:
	      exit(0);
	      break;
	    case SDL_KEYDOWN:
	      switch (event.key.keysym.sym)
                {
		case SDLK_p:
		  takeScreenshot("test.bmp");
		  break;
		default:
		  break;
                }
	    default:
	      break;
            }
        }

      current_time = SDL_GetTicks();
      elapsed_time = current_time - last_time;
      last_time = current_time;

      // déplacement caméra
      angle_camera += VITESSE_MOUVEMENT_CAMERA * elapsed_time;
      hauteur = 2 + 2 * cos(2 * angle_camera * M_PI / 180);

      // rotation pyramide
      angle_pyramide +=  VITESSE_ROTATION_PYRAMIDE * elapsed_time;

      // deplacement cube
      angle_cube += VITESSE_DEPLACEMENT_CUBE * elapsed_time;
      x_cube = 2 * cos(angle_cube * M_PI / 180);

      // deplacement caisse
      //      angle_caisse += VITESSE_DEPLACEMENT_CAISSE * elapsed_time;
      //      x_caisse = 2 * cos(angle_caisse * M_PI / 180);

      DrawGL();

      stop_time = SDL_GetTicks();
      if ((stop_time - last_time) < time_per_frame)
        {
	  SDL_Delay(time_per_frame - (stop_time - last_time));
        }

    }

  return 0;
}

void dessinerCaisse()
{
  glBindTexture(GL_TEXTURE_2D, texture1);
  glPushMatrix();
  glTranslated(x_cube,2,0);

  //Je feinte en dessinant la même face 4 fois avec une rotation
  for (int i = 0; i < 4; i++)
    {
      glBegin(GL_QUADS);
      glTexCoord2d(0,1);
      glVertex3d(1,1,1);
      glTexCoord2d(0,0);
      glVertex3d(1,1,-1);
      glTexCoord2d(1,0);
      glVertex3d(-1,1,-1);
      glTexCoord2d(1,1);
      glVertex3d(-1,1,1);
      glEnd();
      glRotated(90,0,0,1);
    }

  //puis le dessus (pas besoin du dessous grâce au sol)
  glBegin(GL_QUADS);
  glTexCoord2d(0,0);
  glVertex3d(1,-1,1);
  glTexCoord2d(1,0);
  glVertex3d(1,1,1);
  glTexCoord2d(1,1);
  glVertex3d(-1,1,1);
  glTexCoord2d(0,1);
  glVertex3d(-1,-1,1);
  glEnd();

  glPopMatrix();
}

void dessinerPyramide()
{

  glBindTexture(GL_TEXTURE_2D, texture2);
  glPushMatrix();
  glTranslated(-1,-1,0);
  glRotated(angle_pyramide,0,0,1);

  //Je feinte en dessinant la même face 4 fois avec une rotation
  for (int i = 0; i < 4; i++)
    {
      glBegin(GL_TRIANGLES);
      glTexCoord2d(0,0);
      glVertex3d(1,1,-1);
      glTexCoord2d(1,0);
      glVertex3d(-1,1,-1);
      glTexCoord2d(0.5,1);
      glVertex3d(0,0,1);
      glEnd();
      glRotated(90,0,0,1);
    }

  glPopMatrix();
}

void dessinerCaisseBois()
{
  glBindTexture(GL_TEXTURE_2D, texture3);
  glPushMatrix();

  // Pour que la caisse en bois soit à l'opposée du cube
  // et fasse le mouvement opposé du cube, il y a 2
  // possibilitées

  // solution 1
  // On translate à l'opposé par rapport à y donc -2
  // On ajoute 2 pour que la caisse ne rentre pas en collision 
  // avec la pyramide donc -4
  // On prend l'opposée de la valeur de x par rapport au cube
  glTranslated(-x_cube,-4,0);

  // solution 2
  // On faire subir une rotation de 180° au repère
  // puis on déplace le cube + 2 pour éviter la pyramide.
  //  glRotated(180,0,0,1);
  //  glTranslated(x_cube,4,0);

  //Je feinte en dessinant la même face 4 fois avec une rotation
  for (int i = 0; i < 4; i++)
    {
      glBegin(GL_QUADS);
      glTexCoord2d(0,1);
      glVertex3d(1,1,1);
      glTexCoord2d(0,0);
      glVertex3d(1,1,-1);
      glTexCoord2d(0.33,0);
      glVertex3d(-1,1,-1);
      glTexCoord2d(0.33,1);
      glVertex3d(-1,1,1);
      glEnd();
      glRotated(90,0,0,1);
    }
  //puis le dessus (pas besoin du dessous grâce au sol)
  glBegin(GL_QUADS);
  glTexCoord2d(0,0);
  glVertex3d(1,-1,1);
  glTexCoord2d(0.33,0);
  glVertex3d(1,1,1);
  glTexCoord2d(0.33,1);
  glVertex3d(-1,1,1);
  glTexCoord2d(0,1);
  glVertex3d(-1,-1,1);
  glEnd();

  glPopMatrix();
}

void DrawGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  gluLookAt(5,5,hauteur,0,0,0,0,0,1);

  glRotated(angle_camera,0,0,1);

  //LE SOL
  glBindTexture(GL_TEXTURE_2D, texture4);
  glBegin(GL_QUADS);
  glColor3ub(255,0,0);
  glTexCoord2i(0,0);
  glVertex3i(-10,-10,-1);
  glColor3ub(0,255,0);
  glTexCoord2i(10,0);
  glVertex3i(10,-10,-1);
  glColor3ub(255,255,0);
  glTexCoord2i(10,10);
  glVertex3i(10,10,-1);
  glColor3ub(255,0,255);
  glTexCoord2i(0,10);
  glVertex3i(-10,10,-1);
  glEnd();

  glColor3ub(255,255,255);

  dessinerCaisseBois();

  glColor3ub(255,255,255);

  dessinerCaisse();

  glColor3ub(255,255,255);

  dessinerRepere(5);

  glColor3ub(255,255,255);

  dessinerPyramide();

  glFlush();
  SDL_GL_SwapBuffers();
}

/*
  Dessine le repère actuel pour faciliter
  la compréhension des transformations.
  Utiliser « echelle » pour avoir un repère bien orienté et positionné
  mais avec une échelle différente.
*/
void dessinerRepere(unsigned int echelle = 1)
{
  glPushMatrix();
  glScalef(echelle, echelle, echelle);

  glBegin(GL_LINES);

  // axe des x
  glColor3ub(255, 0, 0);
  glVertex3i(0, 0, 0);
  glVertex3i(1, 0, 0);

  // axe des y
  glColor3ub(0, 255, 0);
  glVertex3i(0, 0, 0);
  glVertex3i(0, 1, 0);

  // axe des z
  glColor3ub(0, 0, 255);
  glVertex3i(0, 0, 0);
  glVertex3i(0, 0, 1);

  glEnd();

  glPopMatrix();
}
