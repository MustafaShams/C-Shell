#ifndef _COMMANDS_HPP
#define _COMMANDS_HPP

#include "base.hpp"

class Commands : public Base{
public:
    Commands(){ };
    Commands(std::vector<std::string>& cmd, std::string type) :
                Base(cmd, type) {
        arguments = cmd;
        cmd_type = type;
    };

    bool cmd_status;
    std::vector<std::string> arguments;
    std::string cmd_type;


    virtual bool execute() = 0;
};

#endif //_COMMANDS_HPP
