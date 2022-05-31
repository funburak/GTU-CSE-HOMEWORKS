all: clean compile run


clean:
	@rm -f *.o
	@rm -f *.txt
	@rm -f test
	
compile: main.c
	@gcc main.c -o test 
	
run:
	./test
