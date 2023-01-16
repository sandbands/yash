/**
 * @file yash.hh
 * @author your name (you@domain.com)
 * @brief Definitions for main source file
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef YASH_HH
#define YASH_HH

// software meta
#define AUTHOR			"Rammy Aly"
#define VERSION			"0.10.1"
#define BUILD_STABLE 	"stable"
#define BUILD_NIGHTLY 	"nightly"
#define BUILD_BETA 		"beta"
#define BUILD			BUILD_STABLE

// platform meta
#define PLATFORM_WINDOWS	"windows"		// windows
#define PLATFORM_LINUX		"linux"			// linux
#define PLATFOMR_MAC		"mac/osx"		// mac
#define PLATFORM_OTHER		"unknown OS"	// other

#define PLATFORM PLATFORM_WINDOWS

#define HOMEDIR_FETCH 	"USERPROFILE"
#define USER_FETCH		"USER"

#define GET_HOMEDIR 	getenv(HOMEDIR_FETCH)
#define GET_USERNAME	getenv(USER_FETCH)

#include <string>
#include <vector>
#include <cstring>
#include "tokens.hh"



namespace yash {
	// home directory
	extern const std::string HOMEDIR;

	// username
	extern const std::string USERNAME;

	// get working directory
	extern const std::string CWD;

	// input prompt
	extern const std::string PROMPT;

	// global return value
	extern int glob_return;

	// global token
	extern yash::token glob_token;
}

#endif /* YASH_HH */

