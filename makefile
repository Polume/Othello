CC = gcc
CFLAGS = -Wall -g
IFLAGS = -I lSDL2main -lSDL2

all: run

run: game
	./game

game: othello.o GUI.o PVP.o PVC.o main.o
	$(CC) $(CFLAGS) $^ -o $@ $(IFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(IFLAGS)

clean:
	rm -f *.o game *.exe
