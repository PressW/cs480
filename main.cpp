#include "parser.hpp"
#include <iostream>



int main(int argc, char **argv){
	Scanner *scanner = new Scanner("./tests/test2.cm");
	Tree_Node *root = new Tree_Node();
	root->nodeType = PROGRAM;
	Token *t;
	t = scanner->getToken();
	while (t != NULL){
		cout << "Tokens (Phase 1): " << t->value << endl;
		t = scanner->getToken();
	}
	cout << "Building parser\n";
	Parser *parser = new Parser();
	//parser->build_subtree(root,scanner->tokens);
	parser->print_parse_tree();




	delete scanner;
	delete parser;
}
