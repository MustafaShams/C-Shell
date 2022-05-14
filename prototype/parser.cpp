#include "parser.h"

void Parser::parse_input() {
    char_separator<char> sep(" \t", "#;&|");
    tokenizer< char_separator<char> > tok(getUserInput(), sep);
    queue<string> input_queue;

    for (auto &itr : tok) {
        input_queue.push(itr);
    }

    vector<string> input;

    while (true) {
        while (!input_queue.empty()) {
            input.push_back(input_queue.front());
            input_queue.pop();

        }

        if (input_queue.empty()) {
            setTokenVec(input);
            break;
        }
    }
}


