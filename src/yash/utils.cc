/**
 * @file utils.cc
 * @author ARCO DEVELOPMENT (development.arco@gmail.com)
 * @brief Utilities
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <filesystem>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <errno.h>
#include <string>
#include <boost/process.hpp>
#include "yash/utils.hh"
#include "yash/yash.hh"
#include "yash/errors.hh"
#include "yash/yunistd.hh"
#if PLATFORM_ID == PLATFORM_WINDOWS_ID 
#include <Windows.h>
#else
#include <unistd.h>
#endif

namespace yash {
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

	// flush
	void flush() { std::cout << std::flush; }

	// split string
	std::vector<std::string> split_string(const std::string& __string__, const std::string& delim) {
		std::vector<std::string> result = {};
		std::string entry;

		for (int i=0; i<__string__.size(); i++) {
			bool add = true;

			for (int j=0; j<delim.size(); j++) {
				if (__string__[i] == delim[j])
					add = false;
			}

			if (add) {
				// add character to next entry
				entry += __string__[i];
			} else {
				// push entry to vector, then reset entry
				if (entry.size() != 0)
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

	// check if an int is greater than or equal to the required number
	bool check_int(const int& check, const int& required, const bool& message, const bool& args) {
		if (check >= required)
			return true;
		else {
			if (message) {
				if (args)
					yash::error("insufficient arguments. (expected " + std::to_string(required) + ", got " + std::to_string(check) + ")");
				else
					yash::error("insufficient data. (expected " + std::to_string(required) + ", got " + std::to_string(check) + ")");
				
				yash::push_err(&yash::ERR_INSUFFICIENT_DATA);
			}

			return false;
		}
	}

	// check if a string can be converted into an integer
	bool valid_int(const std::string& string, const bool& _unsigned) {
		std::string illegal = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`-=[]\\';/.,~!@#$%^&*()_+{}|:\"<>?";
		if (!(string.size() > 0))
			return false;

		if (_unsigned) {
			for (int i=0; i<string.size(); i++) {
				for (int j=0; j<illegal.size(); j++) {
					if (string[i] == illegal[j])
						return false;
				}
			}
		}
		
		else {
			if (string.size() == 1 && string[0] == '-')
				return false;

			for (int i=0; i<string.size(); i++) {
				for (int j=0; j<illegal.size(); j++) {
					if (string[i] == illegal[j]) {
						if (!(i == 0 && string[i] == '-'))
							return false;
					}
				}
			}
		}

		return true;
	}

	// simple check for ~ (HOME) symbol
	std::string pathify(const std::string& path, const bool& full) {
		// TODO: fix bug which only keeps home dir
		std::string path_new = path;

		if (full) {
			if (path == "~") {
				path_new = yash::HOMEDIR;
			}

			else if (path[0] == '~') {
				std::string path_new = yash::HOMEDIR;
				for (int i=1; i<path.size(); i++)
					path_new += path[i];
			}
		} else {
			if (path == yash::HOMEDIR) {
				path_new = "~";
			} else if (path.starts_with(yash::HOMEDIR)) {
				std::regex rx(path);
				path_new = std::regex_replace(yash::HOMEDIR, rx, "~");
			}
		}

		return path_new;
	}

	// update the prompt string
	void update_prompt() {
		yash::CWD = yash::gcwd();
		yash::PROMPT = std::string("[" + yash::USERNAME + "  " + yash::CWD + "]$ ");
	}

	// change directory
	int cd(std::string path) {
		int result = 1;

		path = yash::pathify(path);

		try {
			yash::ccwd(path);
		} catch (std::filesystem::__cxx11::filesystem_error& e) {
			result = 0;
		}

		if (result) {
			yash::CWD = yash::gcwd();
			yash::update_prompt();
		}

		return result;
	}

	// change directory using OS standard command
	int cdstd(std::string path) {
		return yash::new_process(std::vector<std::string>{"cd", path});
	}

	// trim the last whitespace of a string
	void trim_end(std::string* string) {
		std::string result;
		int final_index = string->size() - 1;

		if (string->size() > 0) {
			// check for whitespace to trim
			if ((*string)[final_index] == ' ') {
				for (int i=0; i < final_index; i++)
					result += (*string)[i];
			}
		} else {
			result = "";
		}

		*string = result;

		// keep repeating until all whitespaces at the end are removed
		trim_end(string);
	}

	// wait
	void wait(unsigned int seconds) {
		sleep(seconds);
	}

	// suspend
	void suspend(unsigned int seconds) {
		sleep(seconds);
	}

	// pause
	void pause(unsigned int seconds) {
		sleep(seconds);
	}

	// create directory
	bool mkdir(const char* path) {
		return std::filesystem::create_directory(path);
	}

	// create directory
	bool mkdir(const std::string& path) {
		return std::filesystem::create_directory(path);
	}

	// remove directory
	bool rmdir(const char* path) {
		return std::filesystem::remove_all(path);
	}

	// remove directory
	bool rmdir(const std::string& path) {
		return std::filesystem::remove_all(path);
	}

	// create directories
	bool mkdirs(const std::vector<char*>& paths) {
		bool _status = true;

		for (int i=0; i<paths.size(); i++) {	
			if (!std::filesystem::create_directory(paths[i]))
				_status = false;
		}
		
		return _status;
	}

	// create directories
	bool mkdirs(const std::vector<std::string>& paths) {
		bool _status = true;

		for (int i=0; i<paths.size(); i++) {	
			if (!std::filesystem::create_directory(paths[i]))
				_status = false;
		}
		
		return _status;
	}

	// remove directories
	bool rmdirs(const std::vector<char*>& paths) {
		bool _status = true;

		for (int i=0; i<paths.size(); i++) {	
			if (!std::filesystem::remove_all(paths[i]))
				_status = false;
		}
		
		return _status;
	}

	// remove directories
	bool rmdirs(const std::vector<std::string>& paths) {
		bool _status = true;

		for (int i=0; i<paths.size(); i++) {	
			if (!std::filesystem::remove_all(paths[i]))
				_status = false;
		}
		
		return _status;
	}

	// make a file
	bool mk(const char* path) {
		bool _status = true;

		std::ofstream file;

		if (std::filesystem::exists(path))
			_status = false;
		else {
			file.open(path, std::fstream::out | std::fstream::trunc);
			file.close();
		}

		return _status;
	}

	// make a file
	bool mk(const std::string& path) {
		bool _status = true;

		std::ofstream file;

		if (std::filesystem::exists(path))
			_status = false;
		else {
			file.open(path, std::fstream::out | std::fstream::trunc);
			file.close();
		}

		return _status;
	}

	// remove a file
	bool rm(const char* path) {
		return !std::remove(path);
	}

	// remove a file
	bool rm(const std::string& path) {
		return !std::remove(path.c_str());
	}

	// make files
	bool mks(const std::vector<char*>& paths) {
		bool _status = true;

		std::ofstream file;

		for (int i=0; i<paths.size(); i++) {
			if (std::filesystem::exists(paths[i]))
				_status = false;
			else {
				file.open(paths[i], std::fstream::out | std::fstream::trunc);
				file.close();
			}
		}

		return _status;
	}

	// make files
	bool mks(const std::vector<std::string>& paths) {
		bool _status = true;

		std::ofstream file;

		for (int i=0; i<paths.size(); i++) {
			if (std::filesystem::exists(paths[i]))
				_status = false;
			else {
				file.open(paths[i], std::fstream::out | std::fstream::trunc);
				file.close();
			}
		}

		return _status;
	}

	// remove files
	bool rms(const std::vector<char*>& paths) {
		bool _status = true;

		for (int i=0; i<paths.size(); i++) {
			if (std::remove(paths[i]))
				_status = false;
		}

		return _status;
	}

	// remove files
	bool rms(const std::vector<std::string>& paths) {
		bool _status = true;

		for (int i=0; i<paths.size(); i++) {
			if (std::remove(paths[i].c_str()))
				_status = false;
		}

		return _status;
	}

	// list directory contents
	/*
	std::vector<std::string> lsdir(const char* path) {
		std::vector<std::string> result;
		
		for (const auto & entry : std::filesystem::directory_iterator(path))
			result.push_back(std::string(entry.path().string()));
		
		return result;
	} */

	// list directory contents
	/*
	std::vector<std::string> lsdir(const std::string& path) {
		std::vector<std::string> result;
		
		for (const auto & entry : std::filesystem::directory_iterator(path))
			result.push_back(std::string(entry.path().c_str().string()));
		
		return result;
	} */

	// create new process
	int new_process(const std::vector<std::string>& argv) {
		// line: get output from child process
		// argv_str: parse vector of strings into one string to pass to the child process
		std::string line, argv_str;

		int argc = argv.size();

		if (argc > 1) {
			for (int i=0; i<argc; i++) {
				if (i == argc - 1) {
					argv_str += argv[i];
				} else {
					argv_str += argv[i] + " ";
				}
			}
		} else {
			argv_str = argv[0];
		}

		boost::process::ipstream pipe_stream;

		try {
			boost::process::child child_process(argv_str.c_str(), boost::process::std_out > pipe_stream);

			while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
				std::cerr << line << std::endl;

			child_process.wait();
			
			return child_process.exit_code();
		}

		catch (boost::process::process_error &error) {
			int code = error.code().value();
			std::cerr << "error-" << code << ": " << error.what() << std::endl;
			yash::push_err(new yash::Error("execerr", std::string(error.what()), code));

			return code;
		}
	}

	// create new process
	int new_process(const std::string& argv) {
		// line: get output from child process
		std::string line;

		boost::process::ipstream pipe_stream;

		try {
			boost::process::child child_process(argv.c_str(), boost::process::std_out > pipe_stream);

			while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
				std::cerr << line << std::endl;

			child_process.wait();
			
			return child_process.exit_code();
		}

		catch (boost::process::process_error &error) {
			int code = error.code().value();
			std::cerr << "error-" << code << ": " << error.what() << std::endl;
			yash::push_err(new yash::Error("execerr", std::string(error.what()), code));

			return code;
		}
	}
}



