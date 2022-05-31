all: clean compile run


clean:
	@rm -f *.o
	@rm -f test
	@rm -f temporary.txt
	
compile: main.c
	@gcc main.c -o test -lm
	
run:
	./test
