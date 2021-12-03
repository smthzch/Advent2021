CFLAGS=-Wall -g

all:
	gcc $(CFLAGS) -o bin/advent src/days.c src/main.c
  
clean:
	rm bin/advent

run:
	bin/advent