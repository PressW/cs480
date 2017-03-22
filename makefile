default: all
COMP = g++
STD = -std=c++11

token.o: token.cpp token.hpp
	$(COMP) $(STD) -c token.cpp token.hpp

scanner.o: token.o scanner.cpp scanner.hpp
	$(COMP) $(STD) -c scanner.cpp scanner.hpp

parser.o: scanner.o parser.cpp parser.hpp
	$(COMP) $(STD) -c parser.cpp parser.hpp 

main: parser.o main.cpp
	$(COMP) $(STD) main.cpp parser.o scanner.o token.o -o compiler

all: parser.o main

clean:
	rm -f *.o *.gch compiler
