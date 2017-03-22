#include "Token.hpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class Scanner{

	public:
		string filename;
		ifstream file;
		Scanner();
		Scanner(string filename);
		~Scanner();
	private:
		
};
