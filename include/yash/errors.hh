/**
 * @file errors.hh
 * @author ARCO DEVELOPMENT (development.arco@gmail.com)
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
#include <vector>

namespace yash {
	// print error
	void error(const std::string& message, const bool& punctuate=true);

	// print error
	void error(const std::string& message, const std::string& item, const bool& punctuate=true);

	class Error {
		public:
		const std::string name, message, type;
		const int code;

		Error(const std::string& name, const std::string& message, const int& code, const std::string& type="Standard Error");
	};

	// print error by reference
	void error(const Error* error, const std::string& item="None", const bool& punctuate=true);

	// error codes
	extern const Error ERR_INSUFFICIENT_ARGUMENTS;
	extern const Error ERR_INVALID_ARGUMENTS;
	extern const Error ERR_INVALID_DATA;
	extern const Error ERR_INSUFFICIENT_DATA;
	extern const Error ERR_INVALID_TOKEN;
	extern const Error ERR_INVALID_SYNTAX;
	extern const Error ERR_INCOMPLETE_OPERATION;
	extern const Error ERR_INVALID_OPERATION;
	extern const Error ERR_ILLEGAL_OPERATION;
	extern const Error ERR_UNKNOWN;
	extern const Error ERR_EXTERNAL;

	extern std::vector<Error*> errors;

	int traceback(int index=1);

	// push error data
	const Error* push_err(const Error* error);
}

#endif /* ERRORS_HH */


