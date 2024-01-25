all: clear compile run

clear:
	@clear
compile:
	@flex -o gpp_lexer.c gpp_lexer.l
	@gcc gpp_lexer.c -o gpp_lexer
run:
	./gpp_lexer test.g++