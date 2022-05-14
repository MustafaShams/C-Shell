#ifndef _ANDCONNECTOR_HPP
#define _ANDCONNECTOR_HPP

#include "operators.hpp"


class AndConnector : public Operators {
public:
    AndConnector() { };
    AndConnector(Base* leftCmd, std::string type) : Operators(leftCmd, type) {
        left = leftCmd;
        cmd_type = type;
    };

    bool cmd_status;
    Base* left;
    std::string cmd_type = "and";

    bool execute() {
        if (left->execute()) {
           cmd_status = true;
           return true;
        } else {
           cmd_status = false;
           return false;
        }
    };
};

#endif //_ANDCONNECTOR_HPP
