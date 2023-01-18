/**
 * @file utils.cc
 * @author Rammy Aly (ramaly544@gmail.com)
 * @brief Utilities
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <filesystem>
#include <cstdio>
#include <iostream>
#include <vector>
#include <errno.h>
#include <string>
#include "yash.hh"
#include "errors.hh"
#include "yunistd.hh"

namespace yash {
	// clear output with escape characters
	void clear_esc() {
		printf("\033[H\033[J");
	}

	// clear output
	void clear(const std::string& platform) {
		if (platform == PLATFORM_WINDOWS)
			std::system("cls");
		else
			std::system("clear");
	}

	// end line
	void endl() { std::cout << std::endl; }

	// parse vector
	template <typename T>
	std::string parse(const std::vector<T>& vector, const std::string& wrap, const std::string& sep) {
		std::string wrap_open, wrap_close;

		// must have exactly two characters. Anything other will default to no wrap
		if (wrap.size() == 2) {
			std::string wrap_open	= wrap[0];
			std::string wrap_close	= wrap[1];
		}

		// no wrap
		else {
			std::string wrap_open	= "";
			std::string wrap_close	= "";
		}

		std::string result = wrap_open;

		if (vector.size() > 0) {
			for (int i = 0; i < vector.size(); i++) {
				// first and last
				if (i == 0 && vector.size() == 1) {
					// add item
					result += vector[i];
					// clsoe wrap
					result += wrap_close;
					return result;
				}

				// first but not last
				else if (i == 0 && vector.size() > 1) {
					result += vector[i];
					result += sep;
				}

				// last item
				else if (i == vector.size() - 1) {
					result += vector[i];
					result += wrap_close;
					return result;
				}

				// any other item
				else {
					result += vector[i];
					result += sep;
				}
			}
		}

		// close wrap
		result += wrap_close;

		return result;
	}

	// split string
	std::vector<std::string> split_string(const std::string& string, const std::string& delim) {
		std::vector<std::string> result;
		std::string entry;

		for (int i=0; i<string.size(); i++) {
			bool add = true;

			for (int j=0; j<delim.size(); j++) {
				if (string[i] == delim[j])
					add = false;
			}

			if (add) {
				// add character to next entry
				entry += string[i];
			} else {
				// push entry to vector, then reset entry
				result.push_back(entry);
				entry = "";
			}
		}

		// if entry is not blank at final state, add it
		if (entry.size() != 0) {
			result.push_back(entry);
		}

		return result;
	}

	// change current working directory
	std::string ccwd(const std::string& path=yash::HOMEDIR) {
		std::filesystem::current_path(path.c_str());
		return path;
	}

	// get current working directory
	std::string gcwd() {
		return std::filesystem::current_path().string();
	}

	// check if an int is greater than or equal to the required number
	bool check_int(const int& check, const int& required, const bool& message, const bool& args) {
		if (check >= required)
			return true;
		else {
			if (message) {
				if (args)
					yash::error("insufficient arguments. (expected " + std::to_string(required) + ", got " + std::to_string(check) + ")");
				else
					yash::error("insufficient data. (expected " + std::to_string(required) + ", got " + std::to_string(check) + ")");
				
				yash::push_err(&yash::ERR_INSUFFICIENT_DATA);
			}

			return false;
		}
	}

	// check if a string can be converted into an integer
	bool valid_int(const std::string& __string, const bool& __unsigned) {
		std::string illegal = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`-=[]\\';/.,~!@#$%^&*()_+{}|:\"<>?";
		if (!(__string.size() > 0))
			return false;

		if (__unsigned) {
			for (int i=0; i<__string.size(); i++) {
				for (int j=0; j<illegal.size(); j++) {
					if (__string[i] == illegal[j])
						return false;
				}
			}
		}
		
		else {
			if (__string.size() == 1 && __string[0] == '-')
				return false;

			for (int i=0; i<__string.size(); i++) {
				for (int j=0; j<illegal.size(); j++) {
					if (__string[i] == illegal[j]) {
						if (!(i == 0 && __string[i] == '-'))
							return false;
					}
				}
			}
		}

		return true;
	}

	// simple check for ~ (HOME) symbol
	std::string pathify(std::string& path) {
		if (path == "~")
			path = yash::HOMEDIR;
		else if (path[0] == '~') {
			std::string path_new = yash::HOMEDIR;
			for (int i=0; i<path.size(); i++)
				path_new += path[i];
			path = path_new;
		}

		return path;
	}

	// update the prompt string
	void update_prompt() {
		yash::PROMPT = std::string("[" + yash::USERNAME + "@yash  " + yash::CWD + "]$ ");
	}

	// change directory
	int cd(std::string path) {
		int result = 1;

		if (path == "~")
			path = yash::HOMEDIR;

		try {
			yash::ccwd(pathify(path));
		} catch (std::filesystem::__cxx11::filesystem_error& e) {
			result = 0;
		}

		if (result) {
			yash::CWD = yash::gcwd();
			update_prompt();
		}

		return result;
	}

	// reverse a vector
	template <typename T>
	std::vector<T> reverse_vector(std::vector<T>& __vector) {
		std::vector<T> __new = {};

		// 2 elements or more
		if (__vector.size() > 0 && __vector.size() != 1) {
			// iterate backwards
			for (int i=__vector.size() - 1; i >= 0; i--)
				__new.push_back(__vector[i]);		
		}

		// 1 element
		else if (__vector.size() == 1) {
			__new.push_back(__vector[0]);
		}

		// 0 elements will return the empty __new vector

		return __new;
	}

	// trim the last whitespace of a string
	void trim_end(std::string* __string) {
		std::string result;
		int final_index = __string->size() - 1;

		if (__string->size() > 0) {
			// check for whitespace to trim
			if ((*__string)[final_index] == ' ') {
				for (int i=0; i < final_index; i++)
					result += (*__string)[i];
			}
		} else {
			result = "";
		}

		*__string = result;

		// keep repeating until all whitespaces at the end are removed
		trim_end(__string);
	}

	// sleep
	void __sleep(unsigned int seconds) {
		sleep(seconds);
	}

	// suspend
	void suspend(unsigned int seconds) {
		sleep(seconds);
	}

	// pause
	void pause(unsigned int seconds) {
		sleep(seconds);
	}
}
