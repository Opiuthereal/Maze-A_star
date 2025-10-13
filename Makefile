# Compilateur
CC = g++
# Dossiers d'include
INCLUDE = -I glad/include
# Librairies à linker
LIBS = -lglfw -ldl -lGL
# Flags
CFLAGS = -Wall -std=c++17 $(INCLUDE)

# Fichiers objets
OBJ = main.o renderable.o face.o shader.o glad.o

# Nom de l'exécutable
TARGET = affichage

# Règle par défaut
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBS) -o $(TARGET)

# Compilation des fichiers source
main.o: main.cpp face.h renderable.h shader.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

renderable.o: renderable.cpp renderable.h shader.h
	$(CC) $(CFLAGS) -c renderable.cpp -o renderable.o

face.o: face.cpp face.h renderable.h
	$(CC) $(CFLAGS) -c face.cpp -o face.o

shader.o: shader.cpp shader.h
	$(CC) $(CFLAGS) -c shader.cpp -o shader.o

glad.o: glad/src/glad.c glad/include/glad/glad.h
	$(CC) $(CFLAGS) -c glad/src/glad.c -o glad.o

# Nettoyer les fichiers compilés
clean:
	rm -f *.o $(TARGET)

