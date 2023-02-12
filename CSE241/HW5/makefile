all: clear clean compile run

clear:
	@clear

clean:
	@rm -f *.o
	@rm -f driver1
	@rm -f driver2
	@rm -f *.txt

compile: tetromino.cpp  TetrisVector.cpp  Tetris1D.cpp TetrisAdapter.cpp driver2.cpp
	@g++ -std=c++11 tetromino.cpp TetrisVector.cpp Tetris1D.cpp TetrisAdapter.cpp driver1.cpp -o driver1
	@g++ -std=c++11 tetromino.cpp TetrisVector.cpp Tetris1D.cpp TetrisAdapter.cpp driver2.cpp -o driver2

run:
	./driver1
	./driver2