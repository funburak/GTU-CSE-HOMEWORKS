all: clean compile run

clean:
	@rm -f *.o
	@rm -f test
	
compile: main.c util.c util.h
	@gcc -o test main.c util.c

run:
	./test


