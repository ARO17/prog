/*
 * first_3d_cube.cpp
 *
 * Ajout du contrôle de la caméra à l'aide des flèches du clavier
 *
 * g++ -Wall first_3d_cube.cpp -o first_3d_cube -lGL -lGLU -lSDL
 *
 */

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <iostream>

using namespace std;

void Dessiner();
void dessinerRepere(unsigned int echelle);

double angleZ = 0;
double angleX = 0;

int main()
{
  SDL_Event event;

  // initialisation de la SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      cerr << "Echec SDL_Init : " << SDL_GetError() << endl;
      return (EXIT_FAILURE);
    }
  
  // SDL initialisee, on active la procedure de sortie en fin de programme
  //atexit(SDL_Quit); // provoque une erreur de segmentation ?

  // titre de la fenêtre
  SDL_WM_SetCaption("SDL GL Application", NULL);

  // assurons nous que le mode "double buffer" est bien demande
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // activation de l'affichage SDL en mode fenetre
  SDL_Surface* pScreen = SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

  // verification de l'activation de l'affichage
  if( !pScreen )
    {
      cerr << "Echec de creation de la fenetre en 640x480 : " << SDL_GetError() << endl;
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

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(70,(double)640/480,1,1000);
  glEnable(GL_DEPTH_TEST);

  Dessiner();

  Uint32 last_time = SDL_GetTicks();
  Uint32 current_time,ellapsed_time;

  for (;;)
    {
      while (SDL_PollEvent(&event))
        {
	  switch(event.type)
            {
	    case SDL_QUIT:
	      exit(0);
	      break;
	    case SDL_KEYDOWN:
	      switch (event.key.keysym.sym)
		{
		case SDLK_UP:
		  break;
		case SDLK_DOWN:
		  break;
		case SDLK_LEFT:

		  break;
		case SDLK_RIGHT:

		  break;
		default:
		  break;
		}
	      break;
	    default:
	      break;
            }
        }

      current_time = SDL_GetTicks();
      ellapsed_time = current_time - last_time;
      last_time = current_time;
      
      angleZ += 0.05 * ellapsed_time;
      angleX += 0.05 * ellapsed_time;

      cout << "ellapsed time : " << ellapsed_time << endl;
      
      Dessiner();

    }

  return 0;
}

void Dessiner()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  gluLookAt(3, 4, 2, 0, 0, 0, 0, 0, 1);

  glPushMatrix();

  glRotated(angleZ,0,0,1);
  glRotated(angleX,1,0,0);

  dessinerRepere(200);

  glBegin(GL_QUADS);

  glColor3ub(255,0,0); //face rouge
  glVertex3d(1,1,1);
  glVertex3d(1,1,-1);
  glVertex3d(-1,1,-1);
  glVertex3d(-1,1,1);

  glColor3ub(0,255,0); //face verte
  glVertex3d(1,-1,1);
  glVertex3d(1,-1,-1);
  glVertex3d(1,1,-1);
  glVertex3d(1,1,1);

  glColor3ub(0,0,255); //face bleue
  glVertex3d(-1,-1,1);
  glVertex3d(-1,-1,-1);
  glVertex3d(1,-1,-1);
  glVertex3d(1,-1,1);

  glColor3ub(255,255,0); //face jaune
  glVertex3d(-1,1,1);
  glVertex3d(-1,1,-1);
  glVertex3d(-1,-1,-1);
  glVertex3d(-1,-1,1);

  glColor3ub(0,255,255); //face cyan
  glVertex3d(1,1,-1);
  glVertex3d(1,-1,-1);
  glVertex3d(-1,-1,-1);
  glVertex3d(-1,1,-1);

  glColor3ub(255,0,255); //face magenta
  glVertex3d(1,-1,1);
  glVertex3d(1,1,1);
  glVertex3d(-1,1,1);
  glVertex3d(-1,-1,1);

  glEnd();

  glPopMatrix();

  glRotated(angleX,1,0,0);

  dessinerRepere(200);

  glBegin(GL_TRIANGLE_FAN);

  glColor3ub(255,0,0); //face rouge
  glVertex3d(0, 1, 3);
  glColor3ub(0,255,0); //face verte
  glVertex3d(-1, -1, 3);
  glColor3ub(0,0,255); //face bleue
  glVertex3d(1, -1, 3);
  glColor3ub(255,255,0); //face jaune
  glVertex3d(-1, 1, 2);
  glColor3ub(0,255,255); //face cyan
  glVertex3d(-1, -1, 3);

  glEnd();

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
