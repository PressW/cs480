#ifndef _TREENODE_HPP
#define _TREENODE_HPP

#include "constants.hpp"
#include <string>

class Tree_Node {
	public:
		int lineNumber;
		int nValue;
		string sValue;
		int nodeType;
		int typeSpecifier;
		string rename;
		bool visited;
		Tree_Node *C1;
		Tree_Node *C2;
		Tree_Node *C3;
		Tree_Node *sibling;

};

#endif
