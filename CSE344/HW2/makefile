all: clear clean compile run

clear:
	@clear

clean:
	@rm -f test
	@rm -f /tmp/fifo1
	@rm -f /tmp/fifo2

compile:
	@gcc -o test main.c

run:
	@./test 15