all: clear clean compile

.PHONY: all clear clean compile
clear:
	@clear

clean:
	@rm -f PideShop
	@rm -f HungryVeryMuch
	@rm -f pideshop.log

compile:
	@gcc -o PideShop PideShop.c -pthread -lm
	@gcc -o HungryVeryMuch HungryVeryMuch.c -pthread -lm