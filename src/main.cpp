#include "parser.hpp"
#include <string>
#include "operators.hpp"

int main() {
    char hostname[253];
    char* login_info;
//    Commented out login@hostname for submission
//    if(gethostname(hostname, 253) == -1)
//        perror("hostname");

//    login_info = getlogin();

    while (true){
        std::string userInput;
        std::vector<std::string> parsedCommands;

//        std::cout << login_info << "@" << hostname << "$ ";
        std::cout << "$ ";

        getline(std::cin, userInput);

        auto* parser = new Parser(userInput);
        parser->parse_input();

        Operators* ops = new Operators(parser->getTokenVec());
        ops->execute();

        delete parser;
        delete ops;
    }

    return 0;
}