#ifndef ___PARSER_H
#define ___PARSER_H

#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <iostream>
#include <boost/tokenizer.hpp>

class Commands;
class SingleCommand;

class Parser {
private:
    std::vector<std::string> tokens;
    std::string userInput;
    std::queue<std::string> input_queue;

    std::string connectorsCheck();
    std::string quotesCheck();
    std::vector<std::string> bracketsCheck();
    void parenthesisCheck();

public:
    explicit Parser(std::string const &inputs){
        setUserInput(inputs);
    };

    std::vector<std::string> parse_input();
    void setUserInput(std::string inputs) { userInput = inputs; };
    std::string getUserInput() { return userInput; };
    void setTokenVec(std::vector<std::string> tokenVec) {
        for (auto &el : tokenVec) tokens.push_back(el); };
    std::vector<std::string> getTokenVec() { return tokens; };
};

#endif //___PARSER_H
