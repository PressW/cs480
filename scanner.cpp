#include "Scanner.hpp"

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
    vector<Token> tokens;
    string data;
    string token_string;
    for (int i = 0; i < lines.size(); ++i){
        data = lines[i];
        token_string = "";
        for (int c = 0; c < data.length(); ++c){
            switch(data[c]){
                default:
                    break;
            }
        }

    }
}
Scanner::~Scanner(){
    file.close();
}
