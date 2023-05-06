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
#include "errors.hh"

namespace yash {
	// clear output with escape characters
	void clear_esc();

	// clear output
	void clear(const std::string& platform=PLATFORM);

	// end line
	void endl();

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
	std::vector<std::string> split_string(const std::string& string, const std::string& delim=" \t");

	// change current working directory
	std::string ccwd(const std::string& path=yash::HOMEDIR);

	// get current working directory
	std::string gcwd();

	// check if an int is greater than or equal to the required number
	bool check_int(const int& check, const int& required, const bool& message=true, const bool& args=true);

	// check if a string can be converted into an integer
	bool valid_int(const std::string& string, const bool& _unsigned=true);

	// simple check for ~ (HOME) symbol
	std::string pathify(const std::string& path, const bool& full=true);

	// update the prompt string
	void update_prompt();

	// change directory
	int cd(std::string path = yash::HOMEDIR);

	// reverse a vector
	template <typename T>
	std::vector<T> reverse_vector(const std::vector<T>& vector) {
		std::vector<T> _new = {};

		// 2 elements or more
		if (vector.size() > 0 && vector.size() != 1) {
			// iterate backwards
			for (int i=vector.size() - 1; i >= 0; i--)
				_new.push_back(vector[i]);		
		}

		// 1 element
		else if (vector.size() == 1)
			_new.push_back(vector[0]);

		// 0 elements will return the empty _new vector

		return _new;
	}

	// trim the last whitespace of a string
	void trim_end(std::string* string);

	// sleep
	void _sleep(unsigned int seconds);

	// suspend
	void suspend(unsigned int seconds);

	// pause
	void pause(unsigned int seconds);

	template <typename T>
	void cleanup(std::vector<T>& __memory__) {
		if (__memory__.size() == 0)
			return;

		for (int i=0; i<__memory__.size(); i++)
			delete __memory__[i];
	}

	// create directory
	bool mkdir(const char* path);

	// create directory
	bool mkdir(const std::string& path);

	// remove directory
	bool rmdir(const char* path);

	// remove directory
	bool rmdir(const std::string& path);

	// create directories
	bool mkdirs(const std::vector<char*>& paths);

	// create directories
	bool mkdirs(const std::vector<std::string>& paths);

	// remove directories
	bool rmdirs(const std::vector<char*>& paths);

	// remove directories
	bool rmdirs(const std::vector<std::string>& paths);

	// make a file
	bool mk(const char* path);

	// make a file
	bool mk(const std::string& path);

	// remove a file
	bool rm(const char* path);

	// remove a file
	bool rm(const std::string& path);

	// make files
	bool mks(const std::vector<char*>& paths);

	// make files
	bool mks(const std::vector<std::string>& paths);

	// remove files
	bool rms(const std::vector<char*>& paths);

	// remove files
	bool rms(const std::vector<std::string>& paths);

	// list directory contents
	std::vector<std::string> lsdir(const char* path);

	// list directory contents
	std::vector<std::string> lsdir(const std::string& path);

	// launch programs
	int launch(const std::vector<std::string>& argv);

	// launch programs
	int launch(const std::string& argv);
}


#endif /* UTILS_HH */
