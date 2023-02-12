all:clean compile run

clean:
	@rm -f *.o
	@rm -f test

compile: main.cpp Tetrominos.cpp Tetrominos.h
	@g++ -std=c++11 main.cpp Tetrominos.cpp -o test

run:
	./test