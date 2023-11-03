# Spécifiez le compilateur
CC = g++

# Options de compilation
CFLAGS = -Wall

# Répertoire pour les fichiers objet
OBJ_DIR = obj

# Liste des fichiers source pour chaque cible
SRCS_PROJETPRELIM = $(wildcard projet_prelim/*.cpp)
SRCS_PROJET = $(wildcard src/*.cpp)
SRCS_PROJETGRAPH = $(wildcard projetgraph/*.cpp)

# Génération des noms des fichiers objet à partir des fichiers source
OBJS_PROJETPRELIM = $(patsubst projet_prelim/%.cpp, $(OBJ_DIR)/projetprelim_%.o, $(SRCS_PROJETPRELIM))
OBJS_PROJET = $(patsubst src/%.cpp, $(OBJ_DIR)/src%.o, $(SRCS_PROJET))
OBJS_PROJETGRAPH = $(patsubst projetgraph/%.cpp, $(OBJ_DIR)/projetgraph_%.o, $(SRCS_PROJETGRAPH))

# Listes des cibles
TARGETS = projetprelim projet projetgraph

# Règle de construction des fichiers objet pour chaque cible
$(OBJ_DIR)/projetprelim_%.o: projet_prelim/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/src%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/projetgraph_%.o: projetgraph/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# Règle de construction des exécutables
all: $(TARGETS)

projetprelim: $(OBJS_PROJETPRELIM)
	$(CC) $(CFLAGS) -o $@ $^

projet: $(OBJS_PROJET)
	$(CC) $(CFLAGS) -o $@ $^

projetgraph: $(OBJS_PROJETGRAPH)
	$(CC) $(CFLAGS) -o $@ $^

# Nettoyage des fichiers objet et des exécutables
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGETS)
