#include "Token.hpp"


Token::Token(int type){
    this->type = type;
    this->name = "";
}
Token::Token(int type, string name){
    this->type = type;
    this->name = name;
}
string Token::toStr(){
    return this->name;
}
bool Token::operator==(Token t){
    if (this->type == t.type && this->name == t.name){
        return true;
    }
    else {
        return false;
    }
}

Token::~Token(){


}
