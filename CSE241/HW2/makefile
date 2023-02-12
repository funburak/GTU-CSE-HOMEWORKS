all: clear clean compile run

clear:
	@clear

clean:
	@rm -f *.o
	@rm -f driver1
	@rm -f driver2
	
compile: driver1.cpp driver2.cpp tetris.cpp tetromino.cpp
	@g++ -std=c++11 driver1.cpp tetris.cpp tetromino.cpp -o driver1
	@g++ -std=c++11 driver2.cpp tetris.cpp tetromino.cpp -o driver2

run:
	./driver1
	./driver2
