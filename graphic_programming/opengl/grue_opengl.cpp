/*
 * grue_opengl.cpp
 *
 * g++ -Wall grue_opengl.cpp -o grue_opengl -lGL -lGLU -lSDL
 *
 */

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define LARGEUR_ECRAN 640
#define HAUTEUR_ECRAN 480

#define LONGUEUR_GD_BRAS 300
#define ANGLE_GD_BRAS_MIN 10
#define ANGLE_GD_BRAS_MAX 90

#define LONGUEUR_PT_BRAS 130
#define ANGLE_PT_BRAS_MIN -90
#define ANGLE_PT_BRAS_MAX 90

#define LONGUEUR_FILS_MIN 10
#define LONGUEUR_FILS_MAX 100

#define TAILLE_CAISSE 20

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
  glColor3ub(0, 0, 255);
  glVertex2i(0, 0);
  glVertex2i(1, 0);
  glColor3ub(0, 255, 0);
  glVertex2i(0, 0);
  glVertex2i(0, 1);
  glEnd();
  glPopMatrix();
}

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("La grue !", NULL);
  SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_OPENGL);
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, LARGEUR_ECRAN, 0, HAUTEUR_ECRAN);
  

  bool continuer = true;
  SDL_Event event;
  SDLMod mod = KMOD_NONE;

  int angle_grand_bras = 45;
  int angle_petit_bras = -10;
  int longueur_fils = 50;

  while (continuer)
    {
      SDL_WaitEvent(&event);
      mod = SDL_GetModState();
      switch(event.type)
        {
	case SDL_QUIT:
	  continuer = false;
	  break;
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
	      continuer = false;
	      break;
	    case SDLK_UP:
	      if (longueur_fils > LONGUEUR_FILS_MIN)
		longueur_fils -= 1;
	      break;
	    case SDLK_DOWN:
	      if (longueur_fils < LONGUEUR_FILS_MAX)
		longueur_fils += 1;
	      break;
	    case SDLK_LEFT:
	      if (mod & KMOD_SHIFT) {
		if (angle_grand_bras < ANGLE_GD_BRAS_MAX)
		  angle_grand_bras += 5;
	      } else {
		if (angle_petit_bras < ANGLE_PT_BRAS_MAX)
		  angle_petit_bras += 5;
	      }
	      break;
	    case SDLK_RIGHT:
	      if (mod & KMOD_SHIFT) {
		if (angle_grand_bras > ANGLE_GD_BRAS_MIN)
		  angle_grand_bras -= 5;
	      } else {
		if (angle_petit_bras > ANGLE_PT_BRAS_MIN)
		  angle_petit_bras -= 5;
	      }
	      break;
	    case SDLK_h:
	      /* dessinerRepere(50); */
	      break;
	    default:
	      break;
            }
	  break;
	default:
	  break;
        }

      /* efface le tampon d'affichage */
      glClear(GL_COLOR_BUFFER_BIT);

      /* dessine */

      /* base */
      glPushMatrix();
      glTranslated(20, 20, 0);
      glBegin(GL_QUADS);
      glColor3ub(255, 150, 0);
      glVertex2d(0, 0);
      glVertex2d(0, 40);
      glVertex2d(100, 40);
      glVertex2d(100, 0);
      glEnd();
      glPopMatrix();

      /* grand bras */
      glPushMatrix();
      glTranslated(70, 60, 0);
      glRotated(angle_grand_bras, 0, 0, 1);
      glBegin(GL_QUADS);
      glColor3ub(255, 250, 0);
      glVertex2d(0, -15);
      glVertex2d(0, 15);
      glVertex2d(LONGUEUR_GD_BRAS, 15);
      glVertex2d(LONGUEUR_GD_BRAS, -15);
      glEnd();

      /* petit bras */
      glTranslated(LONGUEUR_GD_BRAS, 0, 0);
      glRotated(angle_petit_bras, 0, 0, 1);
      glBegin(GL_QUADS);
      glColor3ub(50, 250, 50);
      glVertex2d(0, -10);
      glVertex2d(0, 10);
      glVertex2d(LONGUEUR_PT_BRAS, 10);
      glVertex2d(LONGUEUR_PT_BRAS, -10);
      glEnd();
      
      /* fils */
      glTranslated(LONGUEUR_PT_BRAS, 0, 0);
      glRotated(-90 + (angle_petit_bras * -1) + (angle_grand_bras * -1), 0, 0, 1);
      glBegin(GL_LINES);
      glColor3ub(255, 255, 255);
      glVertex2d(0, 0);
      glVertex2d(longueur_fils, 0);
      glEnd();

      /* caisse */
      glTranslated(longueur_fils, 0, 0);
      glBegin(GL_QUADS);
      glColor3ub(255, 0, 0);
      glVertex2d(0, (TAILLE_CAISSE / 2));
      glVertex2d(TAILLE_CAISSE, (TAILLE_CAISSE / 2));
      glVertex2d(TAILLE_CAISSE, -(TAILLE_CAISSE / 2));
      glVertex2d(0, -(TAILLE_CAISSE / 2));
      glEnd();

      /* Restore la matrice de base pour que les modifications
	 qui viennent d'être effectuées ne s'ajoutent pas
	 à chaque fois que les éléments se redessine */
      glPopMatrix();

      /* s'assure que toutes les cmd opengl ont été exécutées */
      glFlush();

      /* échange des buffers back et front */
      SDL_GL_SwapBuffers();
    }

  SDL_Quit();

  return 0;
}
