#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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

        // Create process
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        if (!CreateProcess(NULL, input, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
            printf("Error creating process\n");
            continue;
        }

        // Wait for process to finish
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    return 0;
}
