all: clear clean compile run

clear:
	@clear

clean:
	@rm -f *.o
	@rm -f driver1

compile: driver1.cpp dayofyear.cpp 
	@g++ -std=c++11 driver1.cpp dayofyear.cpp -o driver1

run:
	./driver1