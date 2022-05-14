#ifndef _TESTCOMMAND_HPP
#define _TESTCOMMAND_HPP

#include "commands.hpp"
#include "sys/stat.h"

class TestCommand : public Commands {
public:
    TestCommand () { };
    TestCommand (std::vector<std::string> cmd, std::string type) :
            Commands (cmd, type) {
        arguments = cmd;
        cmd_type = type;
        flag = "e";
        initializeTest();
    };

    std::vector<std::string> arguments;
    std::string cmd_type;
    std::string flag;
    std::string path;

    bool execute();
    void initializeTest();
};

#endif //_TESTCOMMAND_HPP
