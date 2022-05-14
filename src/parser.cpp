#include "parser.hpp"

std::vector<std::string> Parser::parse_input() {
    boost::char_separator<char> sep(" \t", "\";#[]()");
    boost::tokenizer< boost::char_separator<char> > tok(getUserInput(), sep);

    for (auto &itr : tok) {
        //Pushes back tokens to private queue member
        input_queue.push(itr);
    }

    std::vector<std::string> input;

    while (true) {
        //Used to break infinite loop if there are bad connectors/quotes
        bool connectorValid = true;
        bool quotesValid = true;
        bool bracketsValid = true;
        bool parenthesisValid = true;

        while (!input_queue.empty()) {
            if (input_queue.front().front() == '|'
                || input_queue.front().front() == '&'
                || input_queue.front().front() == ';') {
                //Pushes the connectors to input vector, otherwise throw exception
                try{
                    input.push_back(connectorsCheck());
                } catch (const std::invalid_argument& ia) {
                    std::cerr << "Invalid argument: " << ia.what() << std::endl;
                    connectorValid = false;
                    break;
                }
                input_queue.pop();

            } else if (input_queue.front() == "\"") {
                //Pushes the quoted text to input vector, otherwise throw exception
                try {
                    input.push_back(quotesCheck());
                } catch (const std::invalid_argument& ia) {
                    std::cerr << "Invalid argument: " << ia.what() << std::endl;
                    quotesValid = false;
                    break;
                }

            } else if (input_queue.front() == "[") {
                std::vector<std::string> bracket_input;

                try {
                    bracket_input = bracketsCheck();
                } catch (const std::invalid_argument& ia) {
                    std::cerr << "Invalid argument: " << ia.what() << std::endl;
                    bracketsValid = false;
                }

                for (auto el : bracket_input) {
                    input.push_back(el);
                }
            } else if (input_queue.front() == "(") {
                try {
                    parenthesisCheck();
                } catch (const std::invalid_argument& ia) {
                   std::cerr << "Invalid argument: " << ia.what() << std::endl;
                   parenthesisValid = false;
                   break;
                }
                input.push_back(input_queue.front());
                input_queue.pop();

            } else if (input_queue.front() == "#") {
                //Swaps input_queue with an empty queue
                std::queue<std::string>().swap(input_queue);
            } else {
                //Pushes a valid argument to input vector, then pops the queue
                input.push_back(input_queue.front());
                input_queue.pop();
            }
        }

        if (!connectorValid || !quotesValid || !parenthesisValid
            || !bracketsValid) {
            //Breaks without execution if invalid connectors or quotes
            break;
        } else if (input_queue.empty()) {

            setTokenVec(input);
            return input;
        }
    }

    return input;
}

std::string Parser::connectorsCheck(){
    std::queue<std::string> connectors_queue = input_queue;

    if (connectors_queue.front() == "||" || connectors_queue.front() == "&&"
        || connectors_queue.front() == ";"){

        return connectors_queue.front();
    } else {
        throw std::invalid_argument("Incorrect connector syntax.");
    }
}

std::string Parser::quotesCheck() {
    bool endQuote = false;
    std::string quote_input;
    input_queue.pop();

    while (!endQuote) {
        if (input_queue.front() == "\"") {
            quote_input.pop_back();
            input_queue.pop();
            endQuote = true;
        } else {
            quote_input += input_queue.front() + " ";
            input_queue.pop();

            if (input_queue.empty()) {
                throw std::invalid_argument("Missing closing quote.");
            }
        }
    }

    return quote_input;
}

std::vector<std::string> Parser::bracketsCheck() {
    bool endBracket = false;
    std::vector<std::string> bracket_input;
    bracket_input.push_back("test");
    input_queue.pop();

    while (!endBracket) {
        if (input_queue.front() == "]") {
            input_queue.pop();
            endBracket = true;
        } else {
            bracket_input.push_back(input_queue.front());
            input_queue.pop();

            if (input_queue.empty()) {
                throw std::invalid_argument("Missing closing bracket.");
            }
        }
    }

    return bracket_input;
}

void Parser::parenthesisCheck() {
    std::queue<std::string> queue = input_queue;
    std::stack<std::string> stack;
    stack.push(queue.front());
    queue.pop();

    while (!queue.empty()) {
        if (queue.front() == "(") {
            stack.push(queue.front());
            queue.pop();

        } else if (queue.front() == ")") {
            if (stack.empty()) {
                std::cout << stack.size() << std::endl;
                throw std::invalid_argument("Invalid parenthesis syntax.");
            }

            stack.pop();
            queue.pop();
            if (stack.empty())
                break;
        } else {
            queue.pop();
        }
    }

    if (queue.empty() && !stack.empty()) {
        throw std::invalid_argument("Invalid parenthesis syntax.");
    }
}
