# désactivation des règles implicites
.SUFFIXES:

# définition des variables
PROGRAMS = first_3d_cube
CXX = g++
CFLAGS = -Wall -W
LIBS = $(shell sdl-config --libs) -lGL -lGLU


all: $(PROGRAMS)

first_3d_cube: first_3d_cube.cpp
	$(CXX) $(CFLAGS) first_3d_cube.cpp -o first_3d_cube $(LIBS)

# définition des cibles particulières
.PHONY: clean, mrproper
clean:
	rm -rf *.bak rm -rf *.o

mrproper: clean
	rm -rf $(PROGRAMS)
