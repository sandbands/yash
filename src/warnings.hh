/**
 * @file warnings.hh
 * @author Rammy Aly (ramaly544@gmail.com)
 * @brief Output Warnings
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef WARNINGS_HH
#define WARNINGS_HH

#include <string>

namespace yash {
	// print warning
	void warn(const std::string& message, const bool& add_period=true);

	// print warning
	void warn(const std::string& message, const std::string& item, const bool& add_period=true);
}

#endif /* WARNINGS_HH */
