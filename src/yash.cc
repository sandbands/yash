/**
 * @file yash.cc
 * @author ARCO DEVELOPMENT (development.arco@gmail.com)
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
#include "output.hh"

namespace yash {
	// home directory
	extern const std::string HOMEDIR = GET_HOMEDIR;

	// get username
	extern const std::string USERNAME = GET_USERNAME;

	// get working directory
	extern std::string CWD = yash::gcwd();

	// input prompt
	extern std::string PROMPT = std::string("["+ USERNAME + "@yash  " + CWD + "]$ ");
	
	// global return value
	extern int glob_return = 0;

	// global token
	extern yash::token glob_token = TOK_NONE;
}

const std::string help_all() {
	const std::string help_str = "\n\n \
 \n\
 \n\
Available Commands: \n\
 \n\
 gwd\t: Get the current working directory \n\
 exit, quit, q\t: Exit yash \n\
 return [int=?]\t: Exit yash and return an exit code. Default value is the saved return status of the current session \n\
 version, info\t: Displays the build version and info \n\
 clear, cls\t: Clears the screen \n\
 stdout, print [*message=none]\t: Output to the console \n\
 sleep [seconds=1]\t: Sleep for a certain amount of seconds \n\
 throw <name> <code> [*message=\"None\"]\t: Throw an error and assign it information \n\
 trace, traceback (--count, --amount, -ls) | ([index=1])\t: Trace an error's information \n\
 sh, sys, system [*input=none]\t: Execute a system shell command \n\
 mk, make <path>\t: Create a file \n\
 rm, remove <path>\t: Remove a file \n\
 mkdir <path>\t: Create a directory \n\
 rmdir <path>\t: Remove a directory \n\
 mks, makes <*paths>\t: Create files \n\
 rms, removes <*paths>\t: Remove files \n\
 mkdirs <*paths>\t: Create directories \n\
 rmdirs <*paths>\t: Remove directories \n\
\n\n";
	return help_str;
}



// this feature may come back in the near future
// const std::vector<std::string> functions = {}

// this feature may come back in the near future
/* yash::token fn_call(const std::string& function, const std::vector<std::string>& argv, const int& start=2) {
	const int argc = argv.size();
	
	if (function == "print" || function == "stdout") {
		if (check_int(argc, 3)) {
			for (int i=start; i<argc; i++)
				std::cout << argv[i] << ' ';
		}

		std::cout << std::endl;
	}
	
	else {
		yash::error("invalid function");
		yash::push_err(&yash::ERR_INVALID_ARGUMENTS);
	}

	return yash::glob_token;
} */



// execute commands
yash::token exec(std::vector<std::string>& argv) {
	yash::token token = yash::TOK_SUCCESS;

	const int argc = argv.size();

	if (argc > 0) {
		const std::string prog = argv[0];

		// exit
		if (prog == "exit" || prog == "quit" || prog == "q")
			token = yash::TOK_EXIT;
			
		// restart
		else if (prog == "restart")
			token = yash::TOK_RESTART;

		// return and exit
		else if (prog == "return") {
			token = yash::TOK_RETURN;
			
			if (yash::check_int(argc, 2, false)) {
				const std::string code = argv[1];
				yash::glob_return = std::stoi(code);
			}
		}

		// this feature may come back in the near future
		/* else if (prog == "fn") {
			if (yash::check_int(argc, 2, false)) {
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
					yash::push_err(&yash::ERR_INVALID_TOKEN);
				}
			} else {
				yash::error("please provide a valid function to call");
				yash::push_err(&yash::ERR_INVALID_TOKEN);
			}
		} */

		/* // change working directory
		else if (prog == "cd" || prog == "chdir" || prog == "cwd") {
			if (yash::check_int(argc, 2, false)) {
				const std::string path = argv[1];
				if (!yash::cd(path)) {
					yash::error("invalid path", path);
					yash::push_err(&yash::ERR_INVALID_ARGUMENTS);
				}
			} else {
				const std::string path = yash::HOMEDIR;
				if (!yash::cd(path)) {
					yash::error("failed to navigate to home directory");
					yash::push_err(&yash::ERR_UNKNOWN);
				}
			}
		} */

		else if (prog == "gwd") {
			yash::output(yash::gcwd(), false);
		}

		// print to console
		else if (prog == "stdout" || prog == "print") {
			if (yash::check_int(argc, 2, false)) {
				for (int i=1; i<argc; i++)
					std::cout << argv[i] << ' ';
			}

			std::cout << std::endl;
		}

		// clear console
		else if (prog == "clear" || prog == "cls") {
			yash::clear();
		}

		// get help
		else if (prog == "help") {
			std::cout << help_all() << std::endl;
		}

		// version and info
		else if (prog == "version" || prog == "info") {
			std::cout << "\nyash v" << VERSION << " (" << BUILD << ") for " << PLATFORM << '.' << std::endl;
			std::cout << "developed by " << DEVELOPER << ".\n" << std::endl;	
		}

		// trace errors
		else if (prog == "trace" || prog == "traceback") {
			if (yash::check_int(argc, 2, false)) {
				if (argv[1] == "--count" || argv[1] == "--available" || argv[1] == "-ls") {
					yash::output("available errors to trace", std::to_string(yash::errors.size()));
				} else {
					const std::string __index__ = argv[1];
					if (!yash::valid_int(__index__)) {
						yash::error("invalid integer", __index__);
						yash::push_err(&yash::ERR_INVALID_DATA);
					} else {
						const int index = std::stoi(__index__);
						if (!yash::traceback(index))
							yash::output("no errors have been traced");
					}
				}

			} else {
				if (!yash::traceback(1)) {
					yash::output("no errors have been traced");
				}
			}
		}

		// throw custom error
		else if (prog == "throw") {
			if (yash::check_int(argc, 3, false)) {
				std::string name, __code__, message;
				int code;

				if (argc > 3) {
					name 		= argv[1];
					__code__ 	= argv[2];
					for (int i=3; i<argc; i++) {
						// only item
						if (i == 3 && i == argc - 1) {
							message += argv[i];
						}

						// last item
						else if (i != 3 && i == argc - 1) {
							message += argv[i];
						}

						// every other item
						else {
							message += argv[i] + " ";
						}
					}

				} else {
					name 		= argv[1];
					__code__ 	= argv[2];
					message		= "None";
				}

				if (!yash::valid_int(__code__)) {
					yash::error("invalid integer", __code__);
					yash::push_err(&yash::ERR_INVALID_DATA);
				} else {
					code = std::stoi(__code__);
					yash::push_err(new yash::Error(name, message, code, "User Defined Error"));
				}
			} else {
				yash::error("insufficient arguments");
				yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
			}
		}

		// sleep
		else if (prog == "sleep") {
			if (yash::check_int(argc, 2, false)) {
				const std::string __duration__ = argv[1];

				if (!yash::valid_int(__duration__)) {
					yash::error("invalid integer");
					yash::push_err(&yash::ERR_INVALID_DATA);
				} else {
					yash::wait(std::stoi(__duration__));
				}
			} else {
				yash::wait(1);
			}
		}

		// execute system shell commands
		else if (prog == "sh" || prog == "sys" || prog == "system") {
			if (yash::check_int(argc, 2)) {
				std::string cmd;
				
				for (int i=1; i<argc; i++) {
					// only item
					if (i == 1 && i == argc - 1) {
						cmd += argv[i];
					}

					// last item
					else if (i != 1 && i == argc - 1) {
						cmd += argv[i];
					}

					// every other item
					else {
						cmd += argv[i] + " ";
					}
				}
				
				std::system(cmd.c_str());
			} else {
				yash::output("nothing to do");
			}
		}

		// remove
		else if (prog == "rm" || prog == "remove") {
			if (yash::check_int(argc, 2, false)) {
				const std::string path = argv[1];
				if (!yash::rm(path)) {
					yash::error("failed to remove file", path);
				} else {
					yash::output("removed file", path);
				}
			} else {
				yash::error("insufficient arguments");
				yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
			}
		}

		// make
		else if (prog == "mk" || prog == "make") {
			if (yash::check_int(argc, 2, false)) {
				const std::string path = argv[1];
				if (!yash::mk(path)) {
					yash::error("failed to create file", path);
				} else {
					yash::output("created file", path);
				}
			} else {
				yash::error("insufficient arguments");
				yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
			}
		}

		// removes
		else if (prog == "rms" || prog == "removes") {
			if (yash::check_int(argc, 2, false)) {
				for (int i=1; i<argc; i++) {
					if (!yash::rm(argv[1])) {
						yash::error("failed to remove file", argv[i]);
					} else {
						yash::output("removed file", argv[i]);
					}
				 }
			} else {
				yash::error("insufficient arguments");
				yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
			}
		}

		// makes
		else if (prog == "mks" || prog == "makes") {
			if (yash::check_int(argc, 2, false)) {
				for (int i=1; i<argc; i++) {
					if (!yash::mk(argv[1])) {
						yash::error("failed to create file", argv[i]);
					} else {
						yash::output("created file", argv[i]);
					}
				 }
			} else {
				yash::error("insufficient arguments");
				yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
			}
		}

		// mkdir
		else if (prog == "mkdir") {
			if (yash::check_int(argc, 2, false)) {
				const std::string path = argv[1];
				if (!yash::mkdir(path)) {
					yash::error("failed to create directory", path);
				} else {
					yash::output("created directory", path);
				}
			} else {
				yash::error("insufficient arguments");
				yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
			}
		}

		// rmdir
		else if (prog == "rmdir") {
			if (yash::check_int(argc, 2, false)) {
				const std::string path = argv[1];
				if (!yash::rmdir(path)) {
					yash::error("failed to remove directory", path);
				} else {
					yash::output("removed directory", path);
				}
			} else {
				yash::error("insufficient arguments");
				yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
			}
		}

		// mkdirs
		else if (prog == "mkdirs") {
			if (yash::check_int(argc, 2, false)) {
				for (int i=1; i<argc; i++) {
					if (!yash::mkdir(argv[1])) {
						yash::error("failed to create directory", argv[i]);
					} else {
						yash::output("created directory", argv[i]);
					}
				 }
			} else {
				yash::error("insufficient arguments");
				yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
			}
		}

		// rmdirs
		else if (prog == "rmdirs") {
			if (yash::check_int(argc, 2, false)) {
				for (int i=1; i<argc; i++) {
					if (!yash::rmdir(argv[1])) {
						yash::error("failed to remove directory", argv[i]);
					} else {
						yash::output("removed directory", argv[i]);
					}
				 }
			} else {
				yash::error("insufficient arguments");
				yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
			}
		}

		// current-session yash manipulation
		else if (prog.starts_with("yash.")) {
			if (prog == "yash.") {
				yash::error("vague configuration statement");
				yash::push_err(&yash::ERR_INVALID_SYNTAX);
			}

			else if (prog == "yash.opt") {
				if (argc > 1) {
					const std::string variable = argv[1];

					// set prompt
					if (variable == "prompt" || variable == "prompt=") {
						if (argc == 2 && variable != "prompt=") {
							yash::error("missing operation");
							yash::push_err(&yash::ERR_INCOMPLETE_OPERATION);
						}

						// yash.opt prompt =
						else if (argc == 3 && argv[2] == "=" && variable != "prompt=") {
							yash::error("insufficient data. please provide a value.");
							yash::push_err(&yash::ERR_INSUFFICIENT_DATA);
						}

						// yash.opt prompt=
						else if (argc == 2 && variable == "prompt=") {
							yash::error("insufficient data. please provide a value.");
							yash::push_err(&yash::ERR_INSUFFICIENT_DATA);
						}

						// if user provides data (with "yash.opt prompt =")
						else if (argc > 3) {
							std::string value;
							if (argv[2].size() > 1) {
								for (int i=1; i<argv[2].size(); i++) {
									value += argv[2][i];
								}
							}

							for (int i=3; i<argc; i++) {
								// only item passed
								if (i == 0 && argc == 4) {
									value += argv[i];
								}

								// first item passed
								else if (i == 0 && argc > 4) {
									value += argv[i] + " ";
								}

								// last item
								else if (i == argc - 1) {
									value += argv[i];
								}

								// any other item
								else {
									value += argv[i] + " ";
								}
							}

							yash::PROMPT = value;
						}

						// if user provides data (with "yash.opt prompt=")
						else if (argc > 2) {
							std::string value;
							if (argv[1].size() > std::string("prompt=").size()) {
								for (int i=std::string("prompt=").size(); i<argv[1].size(); i++) {
									value += argv[1][i];
								}
							}

							for (int i=2; i<argc; i++) {

								// only item passed
								if (i == 0 && argc == 3) {
									value = argv[i];
								}

								// first item passed
								else if (i == 0 && argc > 3) {
									value = argv[i] + " ";
								}

								// last item
								else if (i == argc - 1) {
									value = argv[i];
								}

								// any other item
								else {
									value = argv[i] + " ";
								}
							}

							yash::PROMPT = value;
						}
					}

				} else {
					yash::error("missing variable to manipulate");
                    yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
				}
			}

			else {
				yash::error("invalid yash manipulation statement");
				yash::push_err(&yash::ERR_INVALID_DATA);
			}
		}

		else {
			yash::new_process(argv);
		}
	}
	
	else {
		token = yash::TOK_BLANK;
	}

	yash::glob_token = token;

	return token;
}

// loop
yash::token loop(const std::string& prompt) {
	yash::token token = yash::TOK_SUCCESS;

	std::string input;
	std::vector<std::string> argv;
	std::cout << prompt;
	std::getline(std::cin, input);

	argv = yash::split_string(input);

	const int argc = argv.size();

	return exec(argv);
}

// entry
int main(int argc, char* argv[]) {
	// start in home directory
	yash::cd(yash::HOMEDIR);

	bool launch = false;

	if (argc > 1) {
		const std::string prog = std::string(argv[1]);

		// get yash info
		if (prog == "-v" || prog == "--version" || prog == "-i" || prog == "--info") {
			std::cout << "\nyash v" << VERSION << " (" << BUILD << ") for " << PLATFORM << '.' << std::endl;
			std::cout << "developed by " << DEVELOPER << '.' << std::endl;
		}

		// execute single command
		else if (prog == "-c" || prog == "--command") {
			if (argc > 2) {
				std::vector<std::string> argv_new;

				for (int i=2; i<argc; i++)
					argv_new.push_back(std::string(argv[i]));

				return (int) exec(argv_new);
			}
			
			else {
				yash::error("insufficient arguments");
				yash::push_err(&yash::ERR_INSUFFICIENT_ARGUMENTS);
			}

			return yash::glob_return;
		}

		// set working directory and launch
		else if (prog == "-d" || prog == "--directory" || "--wdir" || prog == "-ld") {
			if (argc > 2) {
				const std::string path = std::string(argv[1]);
				if (yash::cd(path)) {
					launch = true;
				} else {
					yash::error("failed to set working directory");
					yash::push_err(&yash::ERR_INVALID_DATA);
				}
			}
		}

		else {
			yash::error("invalid arguments");
			yash::push_err(&yash::ERR_INVALID_ARGUMENTS);
		}

		if (!launch)
			return yash::glob_return;;
	}

	while (1) {
		int token = loop();
		int return_value = yash::glob_return;

		if (token == yash::TOK_EXIT || yash::glob_token == yash::TOK_EXIT)
			return return_value;

		else if (token == yash::TOK_RETURN || yash::glob_token == yash::TOK_RETURN)
			return return_value;

		else if (token == yash::TOK_RESTART) {
			yash::glob_token	= yash::TOK_NONE;
			yash::glob_return 	= 0;
			continue;
		}
	}

	yash::cleanup(yash::errors);

	return yash::glob_return;
}





