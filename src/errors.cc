/**
 * @file errors.cc
 * @author Rammy Aly (ramaly544@gmail.com)
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
#include "yash.hh"
#include "output.hh"
#include "utils.hh"

namespace yash {
	// print error
	void error(const std::string& message, const bool& add_period) {
		if (message.size() > 0) {
			if (message[message.size() - 1] != '.' && add_period)
				printf("\nyash: error: %s.\n\n", message.c_str());
			else
				printf("\nyash: error: %s\n\n", message.c_str());
		}
	}

	// print error
	void error(const std::string& message, const std::string& item, const bool& add_period) {
		if (message.size() > 0) {
			if (message[message.size() - 1] != '.' && add_period)
				printf("\nyash: error: %s: '%s'.\n\n", message.c_str(), item.c_str());
			else
				printf("\nyash: error: %s: '%s'\n\n", message.c_str(), item.c_str());
		}
	}


	Error::Error(const std::string& name, const std::string& message, const int& code, const std::string& type)
		: name(name), message(message), code(code), type(type) {}

	// print error by reference
	void error(const Error* error, const std::string& item, const bool& add_period) {
		if (error->message.size() > 0) {
			if (error->message[error->message.size() - 1] != '.' && add_period)
				printf("\nyash (type:%s,  code:%i,  item:'%s') %s: %s.\n\n", error->type.c_str(), error->code, item.c_str(), error->name.c_str(), error->message.c_str());
			else
				printf("\nyash (type:%s, code:%i,  item:'%s') %s: %s\n\n", error->type.c_str(), error->code, item.c_str(), error->name.c_str(), error->message.c_str());
		}
	}

	// error codes
	extern const Error ERR_INSUFFICIENT_ARGUMENTS 	= Error("ERR_INSUFFICIENT_ARGUMENTS", "insufficient arguments", 101);
	extern const Error ERR_INVALID_ARGUMENTS 		= Error("ERR_INVALID_ARGUMENTS", "invalid arguments", 102);
	extern const Error ERR_INVALID_DATA				= Error("ERR_INVALID_DATA", "invalid data", 103);
	extern const Error ERR_INSUFFICIENT_DATA		= Error("ERR_INSUFFICIENT_DATA", "insufficient data", 104);
	extern const Error ERR_INVALID_TOKEN			= Error("ERR_INVALID_TOKEN", "invalid token", 105);
	extern const Error ERR_UNKNOWN					= Error("ERR_UNKNOWN", "unknown error", 106);

	// list of encountered errors
	extern std::vector<Error*> errors = {};

	int traceback(int index) {
		int result = 1;

		if (yash::errors.size() > 0) {
			if (index > 0 && index <= yash::errors.size()) {
				std::vector<yash::Error*> __errors__ = yash::reverse_vector(yash::errors);
				yash::error(__errors__[index - 1]);
			} else {
				yash::error("no error found at index", std::to_string(index));
				yash::push_err(&yash::ERR_INVALID_DATA);
				result = 0;
			}
		} else {
			yash::output("no errors found");
			result = 0;
		}

		return result;
	}

	// push error data
	const Error* push_err(const Error* error) {
		// set token to error token
		yash::glob_token = yash::TOK_ERROR;
		// set global return to error code
		yash::glob_return = error->code;
		// add error to error list
		yash::errors.push_back( (Error*) error );
		// return error
		return error;
	}
}

