default: all

token.o: token.cpp token.hpp
	g++ -c token.cpp token.hpp

scanner.o: token.o scanner.cpp scanner.hpp
	g++ -c scanner.cpp scanner.hpp

parser.o: scanner.o parser.cpp parser.hpp
	g++ -c parser.cpp parser.hpp 

main: parser.o main.cpp
	g++ main.cpp parser.o scanner.o token.o -o compiler

all: parser.o main

clean:
	rm -f *.o *.gch compiler
