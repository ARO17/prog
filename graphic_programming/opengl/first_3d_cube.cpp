/*
 * first_3d_cube.cpp
 *
 * g++ -Wall first_3d_cube.cpp -o first_3d_cube -lGL -lGLU -lSDL
 *
 */

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <iostream>

void Dessiner();

double angleZ = 0;
double angleX = 0;

int main(int argc, char *argv[])
{
  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  SDL_WM_SetCaption("SDL GL Application", NULL);
  SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

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
            }
        }

      current_time = SDL_GetTicks();
      ellapsed_time = current_time - last_time;
      last_time = current_time;
      
      angleZ += 0.05 * ellapsed_time;
      angleX += 0.05 * ellapsed_time;

      std::cout << "ellapsed time : " << ellapsed_time << std::endl;
      
      Dessiner();

    }

  return 0;
}

void Dessiner()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  gluLookAt(3,4,2,0,0,0,0,0,1);

  glRotated(angleZ,0,0,1);
  glRotated(angleX,1,0,0);

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

  glFlush();
  SDL_GL_SwapBuffers();
}
