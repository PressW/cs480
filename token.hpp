#include <string>
#include <iostream>

using namespace std;

enum CONSTANTS {
	ERROR,
	ELSE,
	IF,
	INT,
	RETURN,
	VOID,
	WHILE,
	PLUS,
	MINUS,
	MULT,
	DIV,
	LS,
	LEQ,
	GT,
	GEQ,
	EQ,
	NEQ,
	ASSIGN,
	SEMI,
	COMMA,
	LPAREN,
	RPAREN,
	LBRACKET,
	RBRACKET,
	LBRACE,
	RBRACE,
	READ,
	WRITE,
	NUMBER,
	ID,
	PROGRAM,
	DECLARATION,
	VARIABLE,
	ARRAY,
	FUNCTION,
	EXPRESSION,
	CALL,
	COMPOUND,
	TYPE_SPECIFIER,
	PARAMETER_LIST,
	PARAMETER,
	STATEMENT_LIST,
	STATEMENT,
	ARGUMENTS
};


class Token {
	
	public:
		int type;
		string name;
		
		Token(int type);
		Token(int type, string value);
		string toStr();
		bool operator==(Token t);
		~Token();

	private:

};
