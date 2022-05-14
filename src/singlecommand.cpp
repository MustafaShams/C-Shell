#include "singlecommand.hpp"

bool SingleCommand::execute() {
    std::vector<char*> args(this->arguments.size() + 1);

    if (this->arguments.at(0) == "exit") {
        exit();
    }
    for (int i = 0; i < this->arguments.size(); ++i){
       args[i] = &this->arguments[i][0];
    }
    args[ this->arguments.size() ] = NULL;

    auto pid = fork();

    if (pid < 0){
        perror("Fork issue.");
        ::exit(1);
    } else if (pid == 0) {
        if (execvp(args[0], args.data()) == -1){
            perror("Execvp failed");
            std::exit(1);
        }
    } else {
        int status, waitPID;
        waitPID = waitpid(pid, &status, WUNTRACED);
        if (waitPID == -1) {
        } else if (WEXITSTATUS(status) == 0) {
            //if child terminated successfully, return true
            cmd_status = true;
            return true;
        } else if (WEXITSTATUS(status) != 0){
            //if child terminated unsuccessfully, return false
            cmd_status = false;
            return false;
        }
    }

    return true;
}

void SingleCommand::exit() {
    ::exit(0);
}

