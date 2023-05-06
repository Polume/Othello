CC = gcc
CFLAGS = -Wall -std=c99
IFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer `pkg-config --cflags --libs gtk+-3.0` -lm

all: install-deps run 

install-deps:
	sudo apt-get install libsdl2-image-dev libsdl2-ttf-dev libsdl2-dev libsdl2-mixer-dev build-essential libgtk-3-dev

run: game
	./game

game: othello.o linked_list.o main.o GUI.o GUI_init.o PVC.o control.o
	$(CC) $(CFLAGS) $^ -o $@ $(IFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(IFLAGS)

clean:
	rm -f *.o game *.exe