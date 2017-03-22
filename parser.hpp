#include "scanner.hpp"
#include "treenode.hpp"
#include <list>
#include <vector>
using namespace std;
class Parser{

	public:
		Parser();
		~Parser();
		void show_tree(Tree_Node *root_node,string prefix);
		void find_siblings(Tree_Node *root_node, vector<Token> token_list);
		void find_arguments(Tree_Node root_node, vector<Token> token_list);
		void find_expression(Token first_token, Tree_Node *root_node, vector<Token> toke_list);
		void find_statement_list_siblings(Tree_Node root_node, vector<Token> token_list);
		void build_subtree(Tree_Node root_node, vector<Token> token_list);

	private:
};
