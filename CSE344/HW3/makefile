all: clear clean compile run

clear:
	@clear

clean:
	@rm -f park

compile:
	@gcc -pthread -o park main.c

run:
	@valgrind ./park