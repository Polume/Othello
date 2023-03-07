CC = gcc
CFLAGS = -Wall -g
IFLAGS = -I lSDL2main -lSDL2

all: run

run: othello
	./othello

othello: othello.o main.o
	$(CC) $(CFLAGS) $^ -o $@ $(IFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(IFLAGS)

clean:
	rm -f *.o othello *.exe
