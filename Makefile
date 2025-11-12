CC = g++

laby: labyrinth.o agent.o main.o
	$(CC) -o laby labyrinth.o agent.o main.o

main.o: main.cpp agent.h labyrinth.h
	$(CC) -c main.cpp

labyrinth.o: labyrinth.cpp agent.h labyrinth.h
	$(CC) -c labyrinth.cpp

agent.o: agent.cpp agent.h labyrinth.h
	$(CC) -c agent.cpp	

clean:
	rm *.o laby
