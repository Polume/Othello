CC = gcc
CFLAGS = -Wall -std=c99
IFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

all: run

run: game
	./game

game: othello.o linked_list.o main.o GUI.o GUI_init.o PVP.o PVC.o
	$(CC) $(CFLAGS) $^ -o $@ $(IFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(IFLAGS)

clean:
	rm -f *.o game *.exe