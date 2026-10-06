CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

rbt: main.o red_black_tree.o
	$(CC) $(CFLAGS) main.o red_black_tree.o -o rbt

main.o: main.c red_black_tree.h
	$(CC) $(CFLAGS) -c main.c

red_black_tree.o: red_black_tree.c red_black_tree.h
	$(CC) $(CFLAGS) -c red_black_tree.c

clean:
	rm -f *.o rbt
