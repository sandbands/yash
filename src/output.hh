/**
 * @file output.hh
 * @author Rammy Aly (ramaly544@gmail.com)
 * @brief Output functions
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef OUTPUT_HH
#define OUTPUT_HH

#include <string>

namespace yash {
	// print
	void output(const std::string& message, const bool& punctuate=true);

	// print
	void output(const std::string& message, const std::string& item, const bool& punctuate=true);
}

#endif /* OUTPUT_HH */
