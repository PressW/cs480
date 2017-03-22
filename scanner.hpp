#include "Token.hpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <regex>


using namespace std;

class Scanner{

	public:
		string filename;
		ifstream file;
		vector<vector<Token*> > all_tokens;
		Scanner();
		Scanner(string filename);
		~Scanner();
		Token* stringToToken(string tokenString);
	private:
		
};
