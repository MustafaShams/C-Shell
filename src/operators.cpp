#include "operators.hpp"
#include "andconnector.hpp"
#include "orconnector.hpp"

void Operators::initializeCommands() {
    std::vector<std::string> current_cmd;
    std::vector<std::string> precedence;
    bool precedenceCheck = false;

    for (int i = 0; i < arguments.size(); ++i) {
        if (arguments.at(i) == "&&") {
            Base* leftCmd;

            if (precedenceCheck) {
                leftCmd = new Operators(precedence);
                precedence.clear();
                precedenceCheck = false;

            } else if (current_cmd.front() == "test") {
                leftCmd = new TestCommand(current_cmd, "test");

            } else {
                leftCmd = new SingleCommand(current_cmd, "command");
            }

            container.push_back(new AndConnector(leftCmd, "and"));
            current_cmd.clear();

        } else if (arguments.at(i) == "||") {
            Base* leftCmd;

            if (precedenceCheck) {
                leftCmd = new Operators(precedence);
                precedence.clear();
                current_cmd.clear();
                precedenceCheck = false;

            } else if (current_cmd.front() == "test") {
                leftCmd = new TestCommand(current_cmd, "test");

            } else {
                leftCmd = new SingleCommand(current_cmd, "command");
            }

            container.push_back(new OrConnector(leftCmd, "or"));
            current_cmd.clear();

        } else if (arguments.at(i) == ";") {
            Base* leftCmd;

            if (precedenceCheck) {
                leftCmd = new Operators(precedence);
                precedence.clear();
                current_cmd.clear();
                precedenceCheck = false;

            } else if (current_cmd.front() == "test") {
                leftCmd = new TestCommand(current_cmd, "test");

            } else {
                leftCmd = new SingleCommand(current_cmd, "command");
            }

            container.push_back(leftCmd);
            current_cmd.clear();

        }
        else if (arguments.at(i) == "(") {
            std::vector<int> indices = findParenthesis();
            
            if (current_cmd.empty()) {
                precedence = initializePrecedence(indices);
                precedenceCheck = true;
                i = last_paren;
            } else {
                std::string str = "(";
                i++;
                while (arguments.at(i) != ")") {
                    str += arguments.at(i) + " ";
                    i++;
                }

                str.pop_back();
                str += ")";
                current_cmd.push_back(str);
            }
        }
        else {
            current_cmd.push_back(arguments.at(i));
        }
    }

    if (!current_cmd.empty() || !precedence.empty()) {
        Base* leftCmd;

        if (precedenceCheck) {
            leftCmd = new Operators(precedence);
            precedence.clear();
            current_cmd.clear();
            precedenceCheck = false;

        } else if (current_cmd.front() == "test") {
            leftCmd = new TestCommand(current_cmd, "test");

        } else {
            leftCmd = new SingleCommand(current_cmd, "command");
        }

        container.push_back(leftCmd);
        current_cmd.clear();
    }
}

bool Operators::execute() {
    this->initializeCommands();

    for (int i = 0; i < container.size(); ++i) {

        if (container.at(i)->execute()) {
            this->cmd_status = true;
        } else {
            if (container.at(i)->cmd_type == "and") {
                this->cmd_status = false;

                while (container.at(i)->cmd_type == "and" &&
                       ++i < container.size()) {
                    
                }
            } else if (container.at(i)->cmd_type == "or") {
                this->cmd_status = true;

                while (container.at(i)->cmd_type == "or" &&
                       ++i < container.size()) {
                    
                }
            }
        }
    }
        return this->cmd_status;
}

std::vector<int> Operators::findParenthesis() {
    bool first_parenthesis = false;
    bool extra = false;
    int first;
    int last;

    if (last_paren == 0) {
        for (int i = 0; i < arguments.size(); ++i) {
            if (!first_parenthesis && arguments.at(i) == "(") {
                first = i;
                first_parenthesis = true;
            } else if (!extra && arguments.at(i) == ")") {
                last = i;
                break;
            } else  {
                if (arguments.at(i) == "(") {
                    extra = true;
                } else if (arguments.at(i) == ")") {
                    extra = false;
                }
            }
        }
    } else {
        for (int i = last_paren + 1; i < arguments.size(); ++i) {
            if (!first_parenthesis && arguments.at(i) == "(") {
                first = i;
                first_parenthesis = true;
            } else if (!extra && arguments.at(i) == ")") {
                last = i;
                break;
            } else  {
                if (arguments.at(i) == "(") {
                    extra = true;
                } else if (arguments.at(i) == ")") {
                    extra = false;
                }
            }
        }
    }


    std::vector<int> indices = {first, last};
    last_paren = last;

    return indices;
}

std::vector<std::string> Operators::initializePrecedence(std::vector<int> index) {
    /*
     * input: {"(", "echo", "test", ")}
     * output: {"echo", "test"}
     */
    std::vector<std::string> precedence_input;
    bool first = false;
    bool extra = false;

    for (int i = index[0] ; i < index[1]; ++i) {
        if (arguments.at(i) == "(" && !first) {
            first = true;
        } else if (arguments.at(i) == ")" && !extra) {
            return precedence_input;

        } else {
            if (arguments.at(i) == "(") {
                extra = true;
                precedence_input.push_back(arguments.at(i));
            } else if (arguments.at(i) == ")") {
                extra = false;
                precedence_input.push_back(arguments.at(i));
            } else {
                precedence_input.push_back(arguments.at(i));
            }
        }
    }

    return precedence_input;
}

