# Compilateur
CC = g++
# Dossiers d'include
INCLUDE = -I glad/include
# Librairies à linker
LIBS = -lglfw -ldl -lGL
# Flags
CFLAGS = -Wall -std=c++17 $(INCLUDE)


affichage: main.o affichage.o glad.o
	$(CC) main.o affichage.o glad.o $(CFLAGS) $(LIBS) -o affichage

main.o: main.cpp affichage.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o
	
affichage.o: affichage.cpp affichage.h
	$(CC) $(CFLAGS) -c affichage.cpp -o affichage.o

glad.o: glad/src/glad.c glad/include/glad/glad.h
	$(CC) $(CFLAGS) -c glad/src/glad.c -o glad.o

# Nettoyer les fichiers compilés
clean:
	rm *.o affichage

