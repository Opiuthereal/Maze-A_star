CC = g++

laby: labyrinth.o agent.o main.o node.o
	$(CC) -Wall -o laby labyrinth.o agent.o main.o node.o

main.o: main.cpp agent.h labyrinth.h
	$(CC) -Wall -c main.cpp

labyrinth.o: labyrinth.cpp agent.h labyrinth.h
	$(CC) -Wall -c labyrinth.cpp

agent.o: agent.cpp agent.h labyrinth.h
	$(CC) -Wall -c agent.cpp

node.o: node.cpp node.h
	$(CC) -Wall -c node.cpp

clean:
	rm *.o laby
