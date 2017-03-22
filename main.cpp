#include "Parser.hpp"
#include <iostream>



int main(int argc, char **argv){
	Scanner *scanner = new Scanner();
	Parser *parser = new Parser();



	delete scanner;
	delete parser;
}
