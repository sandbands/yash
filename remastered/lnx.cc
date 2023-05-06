#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::string input;
    char *args[100];
    bool running = true;
    
    while (running) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        char *token = strtok(&input[0], " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(args[0], args);
            std::cout << "Command not found" << std::endl;
            return 0;
        } else if (pid < 0) {
            std::cout << "Error in forking" << std::endl;
        } else {
            // Parent process
            wait(NULL);
        }
    }
    
    return 0;
}
