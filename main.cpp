#include "parser.hpp"
#include <iostream>

/*
    Andy Garcia: garciaan
    Preston Wipf: wipfp
    CS480 Project
*/

int main(int argc, char **argv){
	Scanner *scanner = new Scanner("./tests/test1.cm");
	Tree_Node *root = new Tree_Node();
	root->nodeType = PROGRAM;
	Token *t;
	t = scanner->getToken();
	while (t != NULL){
//		cout << "Tokens (Phase 1): " << t->value << endl;
		t = scanner->getToken();
	}
	cout << "Building parser\n";
	Parser *parser = new Parser();
    parser->print_parse_tree();
	parser->build_subtree(root,scanner->tokens);




	delete scanner;
	delete parser;
}
