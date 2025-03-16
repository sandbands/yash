/**
 * @file output.cc
 * @author ARCO DEVELOPMENT (development.arco@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstdlib>
#include <string>
#include "yash/output.hh"

namespace yash {
	// print
	void output(const std::string& message, const bool& punctuate) {
		if (message.size() > 0) {
			if (message[message.size() - 1] != '.' && punctuate)
				printf("\nyash: %s.\n\n", message.c_str());
			else
				printf("\nyash: %s\n\n", message.c_str());
		}
	}

	// print
	void output(const std::string& message, const std::string& item, const bool& punctuate) {
		if (message.size() > 0) {
			if (message[message.size() - 1] != '.' && punctuate)
				printf("\nyash: %s: '%s'.\n\n", message.c_str(), item.c_str());
			else
				printf("\nyash: %s: '%s'\n\n", message.c_str(), item.c_str());
		}
	}
}

