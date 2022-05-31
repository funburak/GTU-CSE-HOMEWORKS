all: clean compile run

clean:
	@rm -f *.o
	@rm -f test
	@rm -f *.txt
	

compile: main.c utils.c utils.h
	@gcc -o test main.c utils.c 

run:
	@./test		
	
	
