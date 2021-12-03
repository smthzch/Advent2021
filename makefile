all:
	gcc -Wall -g -o bin/advent src/structs.c src/readin.c src/days.c -lm
  
clean:
	rm bin/advent

run:
	bin/advent
