all:
	mkdir -p bin
	gcc -Wall -g -o bin/advent src/structs.c src/sub.c src/bingo.c src/readin.c src/main.c -lm
  
clean:
	rm bin/advent

run:
	bin/advent
