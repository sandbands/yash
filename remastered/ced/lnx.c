#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    char input[BUFFER_SIZE];
    char* args[BUFFER_SIZE];
    char* token;

    while (1) {
        // Print prompt and read input
        printf("$ ");
        fgets(input, BUFFER_SIZE, stdin);

        // Tokenize input
        int arg_count = 0;
        token = strtok(input, " \n");
        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " \n");
        }
        args[arg_count] = NULL;

        // Exit on "exit" command
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // Create child process
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(args[0], args);
            printf("Command not found\n");
            exit(1);
        } else if (pid > 0) {
            // Parent process
            wait(NULL);
        } else {
            // Error forking process
            printf("Error forking process\n");
        }
    }

    return 0;
}
