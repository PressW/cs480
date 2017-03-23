#include "scanner.hpp"
#include "treenode.hpp"
#include <list>
#include <vector>
using namespace std;
class Parser{

	public:
		Parser();
		//Parser(Scanner *scanner);
		~Parser();
		void show_tree(Tree_Node *root_node,string prefix);
		void find_siblings(Tree_Node *root_node, vector<Token*> token_list);
		void find_arguments(Tree_Node *root_node, vector<Token*> token_list);
		void find_expression(Token *first_token, Tree_Node *root_node, vector<Token*> toke_list);
		void find_statement_list_siblings(Tree_Node *root_node, vector<Token*> token_list);
		void build_subtree(Tree_Node *root_node, vector<Token*> token_list);
		void print_parse_tree();

	private:
};
bool IS_RPAREN(Token *t);
bool IS_LBRACE(Token *t);
bool IS_RBRACE(Token *t);
bool IS_SEMI(Token *t);
bool IS_MINUS(Token *t);
bool IS_MULT(Token *t);
bool IS_NEQ(Token *t);
bool IS_RBRACKET(Token *t);
