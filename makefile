CFLAGS=-Wall -Wshadow -Wextra -g

all:
	mkdir -p bin
	gcc $(CFLAGS) -o bin/advent src/sub.c src/bingo.c src/readin.c src/main.c -lm
  
clean:
	rm bin/advent

run:
	bin/advent
