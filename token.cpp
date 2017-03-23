#include "token.hpp"


Token::Token(int type){
    this->type = type;
    this->value = "";
}
Token::Token(int type, string value){
    this->type = type;
    this->value = value;
}
string Token::toStr(){
    return this->value;
}
bool Token::operator==(Token *t){
    if (this->type == t->type && this->value == t->value){
        return true;
    }
    else {
        return false;
    }
}

Token::~Token(){


}
