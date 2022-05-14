#ifndef _BASE_HPP
#define _BASE_HPP

#include <vector>
#include <iostream>
#include <string>

class Base{
public:
    Base(){ };
    Base(std::vector<std::string> cmd, std::string type) {
        arguments = cmd;
        cmd_type = type;
    };
    Base(Base* leftCmd, std::string type) {
        left = leftCmd;
        cmd_type = type;
    };
    virtual ~Base() { };

    bool cmd_status;
    Base* left;
    std::string cmd_type;
    std::vector<std::string> arguments;

    virtual bool execute() = 0;
};

#endif //RSHELL_BASE_HPP
