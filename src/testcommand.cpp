#include "testcommand.hpp"

bool TestCommand::execute() {
    struct stat buf;
    const char* cmd = path.c_str();

    if (stat(cmd, &buf) == -1) {
        std::cout << "(False)" << std::endl;
        return false;
    } else {
        if (flag == "e") {
            std::cout << "(True)" << std::endl;
            return true;
        } else if (flag == "f") {
            if (S_ISREG(buf.st_mode)) {
                std::cout << "(True)" << std::endl;
                return true;
            } else {
                std::cout << "(False)" << std::endl;
                return false;
            }
        } else if (flag == "d") {
            if (S_ISDIR(buf.st_mode)) {
                std::cout << "(True)" << std::endl;
                return true;
            } else {
                std::cout << "(False)" << std::endl;
                return false;
            }
        }
    }

    return true;
}

void TestCommand::initializeTest() {
    bool testCmd = false;
    for (auto &el : arguments) {
        if (el == "test" && !testCmd) {
            //Do nothing should be the front
            testCmd = true;
        } else if (el.front() == '-') {
            if (el == "-e") {
                flag = "e";
            } else if (el == "-f") {
                flag = "f";
            } else if (el == "-d") {
                flag = "d";
            }
        } else {
            path = el;
        }
    }
}
