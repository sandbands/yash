/**
 * @file errors.hh
 * @author Rammy Aly (ramaly544@gmail.com)
 * @brief Output Errors
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ERRORS_HH
#define ERRORS_HH

#include <string>

namespace yash {
	// print error
	void error(const std::string& message);

	// error codes
	extern const int ERR_INSUFFICIENT_ARGUMENTS;
	extern const int ERR_INVALID_ARGUMENTS;
	extern const int ERR_INVALID_DATA;
	extern const int ERR_INSUFFICIENT_DATA;
	extern const int ERR_INVALID_TOKEN;
	extern const int ERR_UNKNOWN;

	// push error data
	int push_err(const int& __return=yash::ERR_UNKNOWN);
}

#endif /* ERRORS_HH */
