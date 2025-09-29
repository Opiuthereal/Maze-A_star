CC = g++

laby: labyrinth.o agent.o
	$(CC) -o laby labyrinth.o agent.o

labyrinth.o: labyrinth.cpp agent.h labyrinth.h
	$(CC) -c labyrinth.cpp

agent.o: agent.cpp agent.h labyrinth.h
	$(CC) -c agent.cpp	

clean:
	rm *.o laby
