#include "token.hpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <regex>


using namespace std;

class Scanner{

	public:
		int currentLine = 0;
		int posLine = 0;
		string filename;
		ifstream file;
		vector<vector<Token*> > all_tokens;
		Scanner(string filename);
		~Scanner();
		Token* stringToToken(string tokenString);
		Token* getToken();
	private:
		
};
