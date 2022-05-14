#ifndef _OPERATORS_HPP
#define _OPERATORS_HPP

#include "base.hpp"
#include "singlecommand.hpp"
#include "testcommand.hpp"

class Operators : public Base {
public:
    Operators() { };
    Operators(std::vector<std::string> args) { arguments = args; };
    Operators(Base* leftCmd, std::string type) : Base(leftCmd, type) {
        left = leftCmd;
        cmd_type = type;
    };
    ~Operators() {
        for (auto el : container) {
            delete el;
        }

        container.clear();
    };

    bool cmd_status;
    int last_paren = 0;
    Base* left;
    std::string cmd_type;
    std::vector<Base*> container;
    std::vector<std::string> arguments;

    bool execute();
    void initializeCommands();
    std::vector<int> findParenthesis();
    std::vector<std::string> initializePrecedence(std::vector<int>);

};

#endif //_OPERATORS_HPP
