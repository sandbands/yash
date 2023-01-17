/**
 * @file yash.cc
 * @author Rammy Aly (ramaly544@gmail.com)
 * @brief Main source file
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <filesystem>
#include "yash.hh"
#include "utils.hh"
#include "tokens.hh"
#include "errors.hh"
#include "warnings.hh"

namespace yash {
	// home directory
	extern const std::string HOMEDIR = GET_HOMEDIR;

	// get username
	extern const std::string USERNAME = GET_USERNAME;

	// get working directory
	extern const std::string CWD = HOMEDIR;

	// input prompt
	extern const std::string PROMPT = std::string("["+USERNAME+"@yash  " + CWD + "]$ ");
	
	// global return value
	extern int glob_return = 0;

	// global token
	extern yash::token glob_token = TOK_NONE;
}

// functions
std::vector<std::string> functions = {
	"exit",
	"return",
	"print",
	"stdout"
};

bool check_int(const int& check, const int& required, const bool& message=true, const bool& args=true);

yash::token fn_call(const std::string& function, const std::vector<std::string>& argv, const int& start=2) {
	const int argc = argv.size();

	if (function == "exit") {
		yash::glob_token = yash::TOK_EXIT;
	}
	
	else if (function == "return") {
		if (check_int(argc, 3)) {
			const std::string code = argv[2];
			yash::glob_return = std::stoi(code);
		}

		yash::glob_token = yash::TOK_RETURN;
	}
	
	else if (function == "print" || function == "stdout") {
		if (check_int(argc, 3)) {
			for (int i=start; i<argc; i++)
				std::cout << argv[i] << ' ';
		}

		std::cout << std::endl;
	}
	
	else {
		yash::error("invalid function");
		yash::glob_token = yash::TOK_ERROR;
		yash::glob_return = yash::ERR_INVALID_TOKEN;
	}

	return yash::glob_token;
}

bool check_int(const int& check, const int& required, const bool& message, const bool& args) {
	if (check >= required)
		return true;
	else {
		if (message) {
			if (args)
				yash::error("insufficient arguments. (expected " + std::to_string(required) + ", got " + std::to_string(check) + ")");
			else
				yash::error("insufficient data. (expected " + std::to_string(required) + ", got " + std::to_string(check) + ")");
			
			yash::glob_return = yash::ERR_INSUFFICIENT_DATA;
		}

		return false;
	}
	
}

// execute commands
yash::token exec(const std::vector<std::string>& argv) {
	yash::token token = yash::TOK_SUCCESS;

	const int argc = argv.size();

	if (argc > 0) {
		const std::string& prog = argv[0];
		if (prog == "exit")
			token = yash::TOK_EXIT;
			
		else if (prog == "restart")
			token = yash::TOK_RESTART;
			
		else if (prog == "return") {
			token = yash::TOK_RETURN;
			
			if (check_int(argc, 2, false)) {
				const std::string code = argv[1];
				yash::glob_return = std::stoi(code);
			}
		}

		else if (prog == "fn") {
			if (check_int(argc, 2, false)) {
				bool valid_function = false;
				for (int i=0; i<functions.size(); i++) {
					if (argv[1] == functions[i])
						valid_function = true;
				}

				if (valid_function) {
					const std::string function = argv[1];
					token = fn_call(function, argv);
				} else {
					yash::error("invalid function");
					token = yash::TOK_ERROR;
					yash::glob_return = yash::ERR_INVALID_TOKEN;
				}
			} else {
				yash::error("please provide a valid function to call");
				token = yash::TOK_ERROR;
				yash::glob_return = yash::ERR_INVALID_TOKEN;
			}
		}

		else {
			yash::error("invalid command");
			token = yash::TOK_ERROR;
			yash::glob_return = yash::ERR_INVALID_TOKEN;
		}
	}
	
	else
		token = yash::TOK_BLANK;

	yash::glob_token = token;

	return token;
}

// loop
yash::token loop(const std::string& prompt=yash::PROMPT) {
	yash::token token = yash::TOK_SUCCESS;

	std::string input;
	std::vector<std::string> argv;
	std::cout << prompt;
	std::getline(std::cin, input);

	argv = yash::utils::split_string(input);

	const int argc = argv.size();

	return exec(argv);
}

// entry
int main(int argc, char* argv[]) {
	
	if (argc > 1) {
		const std::string prog = std::string(argv[1]);
		if (prog == "-v" || prog == "--version" || prog == "-i" || prog == "--info") {
			std::cout << "\nyash v" << VERSION << " (" << BUILD << ") for " << PLATFORM << '.' << std::endl;
			std::cout << "developed by " << AUTHOR << '.' << std::endl; 
		}

		else if(prog == "-c" || prog == "--command") {
			if (argc > 2) {
				std::vector<std::string> argv_new;

				for (int i=2; i<argc; i++)
					argv_new.push_back(std::string(argv[i]));

				return (int) exec(argv_new);
			}
			
			else {
				yash::error("insufficient arguments");
				return yash::ERR_INSUFFICIENT_ARGUMENTS;
			}
		}

		else {
			yash::error("invalid arguments");
			return yash::ERR_INVALID_ARGUMENTS;
		}

		return 0;
	}

	while (1) {
		int token = loop();
		int return_value = yash::glob_return;

		if (token == yash::TOK_EXIT || yash::glob_token == yash::TOK_EXIT)
			return return_value;

		else if (token == yash::TOK_RETURN || yash::glob_token == yash::TOK_RETURN)
			return return_value;

		else if (token == yash::TOK_RESTART)
			continue;
	}

	return yash::glob_return;
}


