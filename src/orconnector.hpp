#ifndef _ORCONNECTOR_HPP
#define _ORCONNECTOR_HPP

#include "operators.hpp"

class OrConnector : public Operators {
public:
    OrConnector() { };
    OrConnector(Base* leftCmd, std::string type) : Operators(leftCmd, type) {
        left = leftCmd;
        cmd_type = type;
    };

    bool cmd_status;
    Base* left;

    bool execute() {
        //If the left is true, don't fire; if it is false, fire
        cmd_status = !left->execute();

        return cmd_status;
    };
};
#endif //_ORCONNECTOR_HPP
