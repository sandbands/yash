/**
 * @file warnings.cc
 * @author Rammy Aly (ramaly544@gmail.com)
 * @brief Output Warnings
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstdlib>
#include <string>
#include "warnings.hh"

namespace yash {
	// print warning
	void warn(const std::string& message, const bool& add_period) {
		if (message.size() > 0) {
			if (message[message.size() - 1] != '.' && add_period)
				printf("\nyash: warning: %s.\n\n", message.c_str());
			else
				printf("\nyash: warning: %s\n\n", message.c_str());
		}
	}

	// print warning
	void warn(const std::string& message, const std::string& item, const bool& add_period) {
		if (message.size() > 0) {
			if (message[message.size() - 1] != '.' && add_period)
				printf("\nyash: warning: %s: '%s'.\n\n", message.c_str(), item.c_str());
			else
				printf("\nyash: warning: %s: '%s'\n\n", message.c_str(), item.c_str());
		}
	}
}

