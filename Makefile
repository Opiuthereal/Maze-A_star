# Compilateur
CC = g++
# Dossiers d'include
INCLUDE = -I glad/include
# Librairies à linker
LIBS = -lglfw -ldl -lGL
# Flags
CFLAGS = -Wall -std=c++17 $(INCLUDE)

# Fichiers objets
OBJ = main.o renderable.o face.o shader.o cam.o glad.o window.o maze.o renderMaze.o

# Nom de l'exécutable
TARGET = affichage

# Règle par défaut
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBS) -o $(TARGET)

# Compilation des fichiers source
main.o: main.cpp face.h renderable.h shader.h cam.h window.h maze.h renderMaze.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

renderable.o: renderable.cpp renderable.h shader.h face.h
	$(CC) $(CFLAGS) -c renderable.cpp -o renderable.o

face.o: face.cpp face.h renderable.h
	$(CC) $(CFLAGS) -c face.cpp -o face.o

shader.o: shader.cpp shader.h
	$(CC) $(CFLAGS) -c shader.cpp -o shader.o

cam.o: cam.cpp cam.h
	$(CC) $(CFLAGS) -c cam.cpp -o cam.o

glad.o: glad/src/glad.c glad/include/glad/glad.h
	$(CC) $(CFLAGS) -c glad/src/glad.c -o glad.o
	
window.o: window.cpp window.h
	$(CC) $(CFLAGS) -c window.cpp -o window.o
	
maze.o: renderMaze.cpp renderMaze.h maze.h vertex.h shader.h
	$(CC) $(CFLAGS) -c maze.cpp -o maze.o

renderMaze.o: renderMaze.cpp renderMaze.h maze.h shader.h
	$(CC) $(CFLAGS) -c renderMaze.cpp -o renderMaze.o

# Nettoyer les fichiers compilés
clean:
	rm -f *.o $(TARGET)
