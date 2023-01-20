/**
 * @file yash.hh
 * @author Rammy Aly (ramaly544@gmail.com)
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
#define VERSION			"1.08.3"
#define BUILD_STABLE 	"stable"
#define BUILD_NIGHTLY 	"nightly"
#define BUILD_BETA 		"beta"
#define BUILD			BUILD_BETA

// platform meta
#define PLATFORM_WINDOWS	"windows"		// windows
#define PLATFORM_LINUX		"linux"			// linux
#define PLATFOMR_MAC		"mac/osx"		// mac
#define PLATFORM_OTHER		"unknown OS"	// other


// logical representation of platform
#define PLATFORM_WINDOWS_ID 1
#define PLATFORM_LINUX_ID 2
#define PLATFORM_MAC_ID 3
#define PLATFORM_OTHER_ID 4

#ifdef __unix__ || defined(linux) || defined(_linux)
	#define PLATFORM_ID PLATFORM_LINUX_ID
#elif defined(_WIN32) || defined(WIN32)
	#define PLATFORM_ID PLATFORM_WINDOWS_ID
#endif

// string representation of platform
#if PLATFORM_ID == PLATFORM_WINDOWS_ID
	#define PLATFORM PLATFORM_WINDOWS
#elif PLATFORM_ID == PLATFORM_LINUX_ID
	#define PLATFORM PLATFORM_LINUX
#elif PLATFORM_ID == PLATFORM_MAC_ID
	#define PLATFORM PLATFORM_MAC
#else
	#define PLATFORM PLATFORM_OTHER
#endif

// check for platform type
#if PLATFORM_ID == PLATFORM_WINDOWS_ID
	#define HOMEDIR_FETCH 	"USERPROFILE"
	#define USER_FETCH		"USERNAME"
#else
	#define HOMEDIR_FETCH	"HOME"
	#define USER_FETCH		"USER"
#endif

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
	extern std::string CWD;

	// input prompt
	extern std::string PROMPT;

	// global return value
	extern int glob_return;

	// global token
	extern yash::token glob_token;
}

#endif /* YASH_HH */

