CFLAG  = -ansi -pedantic -Wall -Werror
COMPILER = g++ 

all:
	mkdir -p bin

	$(COMPILER) $(CFLAG) src/cd.cpp -o bin/rshell
