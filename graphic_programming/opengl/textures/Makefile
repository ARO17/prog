# désactivation des règles implicites
.SUFFIXES:

# définition des variables
PROGRAMS = textures_opengl
CXX = g++
CFLAGS = -Wall -W
LIBS = $(shell sdl-config --libs) -lSDL_image -lGL -lGLU


all: $(PROGRAMS)

textures_opengl: main.o sdlglutils.o
	$(CXX) $(CFLAGS) main.o sdlglutils.o -o textures_opengl $(LIBS)

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp -o main.o

sdlglutils.o: sdlglutils.cpp
	$(CXX) $(CFLAGS) -c sdlglutils.cpp -o sdlglutils.o

# définition des cibles particulières
.PHONY: clean, mrproper
clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(PROGRAMS)
