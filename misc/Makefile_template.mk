# définition des cibles particulières
# sont exécutées qu'il y ait ou pas un fichier clean, mrproper...
.PHONY: clean, mrproper

# désactivation des règles implicites
.SUFFIXES:

# définition des variables
CC = gcc
EXEC = commande_bras
OBJ = main.o liste.o memoire.o bras.o
DEBUG ?= 0 #0 par défaut

# A appeler de cette façon : make DEBUG=0 ou make DEBUG=1
ifeq ($(DEBUG), 1)
	CFLAGS = -g -W -Wall -DDEBUG
else
	CFLAGS = -W -Wall # -v # mode (trop) verbeux
endif


# all
all: $(EXEC)

# $^ : toutes les dépendances
$(EXEC): $(OBJ)
	$(CC) $^ -o $(EXEC) $(CFLAGS)

# règles d'inférence, règles génériques
# $< : première ou seule dépendance de la liste des dépendances
# $@ : nom de la cible
# %.c pour les cibles
# %.c dans les dépendances
# $*.c dans les commandes
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# On indique une dépendance en dehors des règles d'inférence
# Lorsque memoire.h est modifié, on recompile memoire.c
memoire.o: memoire.h

# clean
# ici on utilise *.bak et pas $.bak car rm est une commande du shell
# et * sera géré par le shell et non pas par make
clean:
	rm -rf *.bak rm -rf *.o

# mrproper
mrproper: clean
	rm -rf $(EXEC)
