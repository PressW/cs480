#include "Parser.hpp"
#include <iostream>



int main(int argc, char **argv){
	Scanner *scanner = new Scanner("./tests/test1.cm");
	Parser *parser = new Parser();
	//parser->parse();


	delete scanner;
	delete parser;
}
