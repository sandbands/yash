#include <iostream>
#include <string>
#include <windows.h>

int main() {
    std::string input;
    bool running = true;
    
    while (running) {
        std::cout << ">> ";
        std::getline(std::cin, input);

        // Convert input to wide string
        std::wstring winput(input.begin(), input.end());
        
        // Create process
        STARTUPINFOW info = { sizeof(info) };
        PROCESS_INFORMATION processInfo;
        if (CreateProcessW(NULL, &winput[0], NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
            WaitForSingleObject(processInfo.hProcess, INFINITE);
            CloseHandle(processInfo.hProcess);
            CloseHandle(processInfo.hThread);
        } else {
            std::cout << "Command not found" << std::endl;
        }

        if (input == "exit") {
            running = false;
        }
    }
    
    return 0;
}
