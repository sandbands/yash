/**
 * @file errors.cc
 * @author your name (you@domain.com)
 * @brief Output Errors
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstdio>
#include <string>
#include "errors.hh"

namespace yash {
	// print error
	void error(const std::string& message) {
		if (message.size() > 0) {
			if (message[message.size() - 1] != '.')
				printf("\n[yash] error: %s.\n\n", message.c_str());
			else
				printf("\n[yash] error: %s\n\n", message.c_str());
		}
	}

	// error codes
	extern const int ERR_INSUFFICIENT_ARGUMENTS = 101;
	extern const int ERR_INVALID_ARGUMENTS 		= 102;
	extern const int ERR_INVALID_DATA			= 103;
	extern const int ERR_INSUFFICIENT_DATA		= 104;
	extern const int ERR_INVALID_TOKEN			= 105;
}

