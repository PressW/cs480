#include "Scanner.hpp"

string trim(string s){
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}

Scanner::Scanner(){

}
Scanner::Scanner(string filename){
    this->filename = filename;
    file.open(filename);
    if (!file.is_open()){
        cout << "Error opening file: " << filename << endl;
        return;
    }
    vector<string> lines;
    string s;
    while(getline(file,s)){
        lines.push_back(s);
    }
    /*
    for (int i = 0; i < lines.size(); ++i){
        cout << lines[i] << endl;
    }*/
    vector<Token*> tokens;
    string data;
    string token_string;
    for (int i = 0; i < lines.size(); ++i){
        data = lines[i];
        token_string = "";
        for (int c = 0; c < data.length(); ++c){
            token_string += data[c];
            switch(data[c]){
                case ' ':
                case '\t':
                    token_string = trim(token_string);
                    if (!token_string.empty()){
                        tokens.push_back(stringToToken(token_string));
                    }
                    break;
                case ';':
                    token_string = token_string.substr(0,token_string.length() - 1);
                    if (!token_string.empty()){
                        tokens.push_back(stringToToken(token_string));
                    }
                    token_string = "";
                    token_string += (data[c]);
                    tokens.push_back(stringToToken(token_string));
                    token_string = "";
                    break;
                case '[':
                    if (token_string != "["){
                        tokens.push_back(stringToToken(token_string.substr(0,token_string.length() - 1)));
                        token_string = "[";
                    }
                    tokens.push_back(stringToToken(token_string));
                    token_string = "";
                    break;
                case '(':
                    if (token_string != "("){
                        tokens.push_back(stringToToken(token_string.substr(0,token_string.length() - 1)));
                        token_string = "(";
                    }
                    tokens.push_back(stringToToken(token_string));
                    token_string = "";
                    break;
                case ')':
                    if (token_string != ")"){
                        tokens.push_back(stringToToken(token_string.substr(0,token_string.length() - 1)));
                        token_string = ")";
                    }
                    tokens.push_back(stringToToken(token_string));
                    token_string = "";
                    break;
                case ',':
                    if (token_string != ","){
                        tokens.push_back(stringToToken(token_string.substr(0,token_string.length() - 1)));
                        token_string = ",";
                    }
                    tokens.push_back(stringToToken(token_string));
                    token_string = "";
                    break;
                case '=':
                    if (token_string != "="){
                        tokens.push_back(stringToToken(token_string.substr(0,token_string.length() - 1)));
                        token_string = "=";
                    }
                    tokens.push_back(stringToToken(token_string));
                    token_string = "";
                    break;
            }
        }
        this->all_tokens.push_back(tokens);
    }
}
Token* Scanner::stringToToken(string tokenString){
    // Token *result = new Token(ERROR,"error");
    cout << "Token found: " << tokenString << endl;
    if (regex_match(tokenString,regex("[0-9]+[.]?[0-9]*$"))){
        return new Token(NUMBER, tokenString);
    }
    else {
        if (tokenString == ""){
            return NULL;
        }
        else if (tokenString == "else"){
            return new Token(ELSE, tokenString);
        }
        else if (tokenString == "if"){
            return new Token(IF,tokenString);
        }
        else if (tokenString == "int"){
            return new Token(INT,tokenString);
        }
        else if (tokenString == "return"){
            return new Token(RETURN,tokenString);
        }
        else if (tokenString == "void")
            return new Token(VOID, tokenString);
        else if (tokenString == "while")
            return new Token(WHILE,tokenString);
        else if (tokenString == "+")
            return new Token(PLUS,tokenString);
        else if (tokenString == "-")
            return new Token(MINUS,tokenString);
        else if (tokenString == "*")
            return new Token(MULT,tokenString);
        else if (tokenString == "/")
            return new Token(DIV,tokenString);
        else if (tokenString == "<")
            return new Token(LS,tokenString);
        else if (tokenString == "<=")
            return new Token(LEQ,tokenString);
        else if (tokenString == ">")
            return new Token(GT,tokenString);
        else if (tokenString == ">=")
            return new Token(GEQ,tokenString);
        else if (tokenString == "==")
            return new Token(EQ,tokenString);
        else if (tokenString == "!=")
            return new Token(NEQ,tokenString);
        else if (tokenString == "=")
            return new Token(ASSIGN,tokenString);
        else if (tokenString == ";")
            return new Token(SEMI,tokenString);
        else if (tokenString == ",")
            return new Token(COMMA,tokenString);
        else if (tokenString == "(")
            return new Token(LPAREN,tokenString);
        else if (tokenString == ")")
            return new Token(RPAREN,tokenString);
        else if (tokenString == "[")
            return new Token(LBRACKET,tokenString);
        else if (tokenString == "]")
            return new Token(RBRACKET,tokenString);
        else if (tokenString == "{")
            return new Token(LBRACE,tokenString);
        else if (tokenString == "}")
            return new Token(RBRACE,tokenString);
        else if (tokenString == "read")
            return new Token(READ,tokenString);
        else if (tokenString == "write")
            return new Token(WRITE,tokenString);
        else {
            return new Token(ID,tokenString);
        }
    }

}
Scanner::~Scanner(){
    file.close();
}
