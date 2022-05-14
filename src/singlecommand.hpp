#ifndef _SINGLECOMMAND_HPP
#define _SINGLECOMMAND_HPP


#include <unistd.h>
#include <sys/wait.h>
#include "commands.hpp"

class SingleCommand: public Commands{
public:
    SingleCommand(std::vector<std::string> cmd, std::string type) :
                    Commands(cmd, type) {
        arguments = cmd;
        cmd_type = type;
    };

    bool cmd_status;
    std::vector<std::string> arguments;
    std::string cmd_type;

    std::vector<std::string> get_cmd() {
        return arguments;
    }

    virtual bool execute();
    void exit();
};


#endif //_SINGLECOMMAND_HPP
