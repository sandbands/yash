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
	void warn(const std::string& message) {
		if (message.size() > 0) {
			if (message[message.size() - 1] != '.')
				printf("\n[yash] warning: %s.\n\n", message.c_str());
			else
				printf("\n[yash] warning: %s\n\n", message.c_str());
		}
	}
}

