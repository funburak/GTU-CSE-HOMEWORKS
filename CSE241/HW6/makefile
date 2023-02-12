all: clear clean compile run

clear:
	@clear

clean:
	@rm -f *.o
	@rm -f test


compile: pfarray.cpp main.cpp
	@g++ -std=c++11 pfarray.cpp main.cpp -o test

run:
	./test
