#ifndef ___PARSER_H
#define ___PARSER_H

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <boost/tokenizer.hpp>
using namespace std;
using namespace boost;

class Parser {
private:
    vector<string> tokens;
    string userInput;

public:
    explicit Parser(string const &inputs){
        setUserInput(inputs);
    };

    void parse_input();
    void setUserInput(string inputs) { userInput = inputs; };
    string getUserInput() { return userInput; };
    void setTokenVec(vector<string> tokenVec) { tokens = tokenVec; };
    vector<string> getTokenVec() { return tokens; };
};

#endif //___PARSER_H
