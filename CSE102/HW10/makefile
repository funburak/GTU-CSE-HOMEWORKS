all: clean compile run

clean:
	@rm -f *.o
	@rm -f test
	
compile: main.c
	@gcc main.c -o test -lm
	
run:
	./test
