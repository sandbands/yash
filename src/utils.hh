/**
 * @file utils.hh
 * @author Rammy Aly (ramaly544@gmail.com)
 * @brief Utilities
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef UTILS_HH
#define UTILS_HH

#include <cstdio>
#include <string>
#include "yash.hh"
#include "yunistd.hh"

namespace yash {
	// clear output with escape characters
	void clear_esc();

	// clear output
	void clear(const std::string& platform=PLATFORM);

	// end line
	void endl();

	// parse vector
	template <typename T>
	std::string parse(std::vector<T> vector, std::string wrap = "()", std::string sep = ", ");

	// split string
	std::vector<std::string> split_string(const std::string& string, const std::string& delim=" \t");

	// change current working directory
	std::string ccwd(const std::string& path=yash::HOMEDIR);

	// get current working directory
	std::string gcwd();

	// check if an int is greater than or equal to the required number
	bool check_int(const int& check, const int& required, const bool& message=true, const bool& args=true);

	// check if a string can be converted into an integer
	bool valid_int(const std::string& __string, const bool& __unsigned=true);

	// simple check for ~ (HOME) symbol
	std::string pathify(std::string& path);

	// update the prompt string
	void update_prompt();

	// change directory
	int cd(std::string path = yash::HOMEDIR);

	// reverse a vector
	template <typename T>
	std::vector<T> reverse_vector(std::vector<T>& __vector);

	// trim the last whitespace of a string
	void trim_end(std::string* __string);

	// sleep
	void __sleep(unsigned int seconds);

	// suspend
	void suspend(unsigned int seconds);

	// pause
	void pause(unsigned int seconds);
}


#endif /* UTILS_HH */
