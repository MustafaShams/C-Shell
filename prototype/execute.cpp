#include <vector>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

bool execute(vector<char*> cmd) {
    auto pid = fork();

    if (pid < 0){
        perror("Fork issue.");
        exit(1);
    } else if (pid == 0) {
        if (-1 == execvp(cmd[0], cmd.data())){
            perror("Execvp failed.");
            exit(1);
        }
    } else {
        int status;
        pid = wait(&status);
        if (WIFEXITED(status)) {
            cout << "pid " << pid << " exited with status: " << status << endl;
        } else{
            cout << "pid " << pid << " exited abnormally." << endl;
        }
    }
    return true;
}
