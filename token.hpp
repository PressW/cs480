#include <string>
#include <iostream>
#include "constants.hpp"
using namespace std;



class Token {
	
	public:
		int type;
		string value;
		
		Token(int type);
		Token(int type, string value);
		string toStr();
		bool operator==(Token *t);
		~Token();

	private:

};
