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

namespace yash {
	namespace utils {
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

		// change current working directory (windows only)
		std::string ccwd_win(const std::string& path=yash::HOMEDIR);
	}
}


#endif /* UTILS_HH */
