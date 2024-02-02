# Compilateur à utiliser
CC = gcc
# Option de compilation (vide)
CFLAGS =

# Fichiers source en C
SRC_C = traitement_s1.c traitement_s2.c
# Fichier script shell
SRC_SH = projet.sh

# Noms des fichiers objets correspondants aux fichiers source en langage C
OBJ_C = $(SRC_C:.c=.o)

# Nom de l'exécutable à produire
EXECUTABLE = mon_programme

all: $(EXECUTABLE) $(SRC_SH)

$(EXECUTABLE): $(OBJ_C)
    $(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
    rm -f $(OBJ_C) $(EXECUTABLE)

run: $(EXECUTABLE)
    ./$(EXECUTABLE)

.PHONY: all clean run
