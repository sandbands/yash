#include <iostream>
#include <string>
#include <boost/process.hpp>

namespace bp = boost::process;

int main() {
    std::string input;
    bool running = true;

    while (running) {
        std::cout << ">> ";
        std::getline(std::cin, input);

        // Create command line
        std::vector<std::string> args = bp::split_cmdline(input);

        // Create process
        bp::ipstream output;
        bp::child c(args[0], bp::args(args), bp::std_out > output);
        c.wait();

        // Read output
        std::string line;
        while (std::getline(output, line)) {
            std::cout << line << std::endl;
        }

        if (input == "exit") {
            running = false;
        }
    }

    return 0;
}
