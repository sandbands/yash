/**
 * @file utils.cc
 * @author Rammy Aly (ramaly544@gmail.com)
 * @brief Utilities
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <filesystem>
#include <cstdio>
#include <iostream>
#include <vector>
#include <direct.h>
#include <errno.h>
#include <string>
#include "yash.hh"
#include "errors.hh"

namespace yash {
	namespace utils {
		// clear output with escape characters
		void clear_esc() {
			printf("\033[H\033[J");
		}

		// clear output
		void clear(const std::string& platform) {
			if (platform == PLATFORM_WINDOWS)
				std::system("cls");
			else
				std::system("clear");
		}

		// end line
		void endl() { std::cout << std::endl; }

		// parse vector
		template <typename T>
		std::string parse(const std::vector<T>& vector, const std::string& wrap, const std::string& sep) {
			std::string wrap_open, wrap_close;

			// must have exactly two characters. Anything other will default to no wrap
			if (wrap.size() == 2) {
				std::string wrap_open	= wrap[0];
				std::string wrap_close	= wrap[1];
			}

			// no wrap
			else {
				std::string wrap_open	= "";
				std::string wrap_close	= "";
			}

			std::string result = wrap_open;

			if (vector.size() > 0) {
				for (int i = 0; i < vector.size(); i++) {
					// first and last
					if (i == 0 && vector.size() == 1) {
						// add item
						result += vector[i];
						// clsoe wrap
						result += wrap_close;
						return result;
					}

					// first but not last
					else if (i == 0 && vector.size() > 1) {
						result += vector[i];
						result += sep;
					}

					// last item
					else if (i == vector.size() - 1) {
						result += vector[i];
						result += wrap_close;
						return result;
					}

					// any other item
					else {
						result += vector[i];
						result += sep;
					}
				}
			}

			// close wrap
			result += wrap_close;

			return result;
		}

		// split string
		std::vector<std::string> split_string(const std::string& string, const std::string& delim) {
			std::vector<std::string> result;
			std::string entry;

			for (int i=0; i<string.size(); i++) {
				bool add = true;

				for (int j=0; j<delim.size(); j++) {
					if (string[i] == delim[j])
						add = false;
				}

				if (add) {
					// add character to next entry
					entry += string[i];
				} else {
					// push entry to vector, then reset entry
					result.push_back(entry);
					entry = "";
				}
			}

			// if entry is not blank at final state, add it
			if (entry.size() != 0) {
				result.push_back(entry);
			}

			return result;
		}

		// change current working directory
		std::string ccwd(const std::string& path) {
			std::filesystem::current_path(path.c_str());
			return path;
		}

		// get current working directory
		std::string gcwd() {
			return std::filesystem::current_path().string();
		}

		// change current working directory (windows only)
		std::string ccwd_win(const std::string& path) {
			// windows only
			if(_chdir(path.c_str())) {
				switch (errno) {
					case ENOENT:
						yash::error("'" + path + "' is not a valid directory");
						yash::glob_return = yash::ERR_INVALID_DATA;
						yash::glob_token = yash::TOK_ERROR;
						break;
					case EINVAL:
						yash::error("Invalid buffer");
						yash::glob_return = yash::ERR_INVALID_DATA;
						yash::glob_token = yash::TOK_ERROR;
						break;
					default:
						yash::error("Unknown error.\n");
						yash::glob_return = yash::ERR_INVALID_DATA;
						yash::glob_token = yash::TOK_ERROR;
						break;
				}
			}

			return path;
		}
	}
}
