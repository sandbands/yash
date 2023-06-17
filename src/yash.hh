/**
 * @file yash.hh
 * @author ARCO DEVELOPMENT (development.arco@gmail.com)
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
#define DEVELOPER		"ARCO DEVELOPMENT"
#define VERSION			"3.14.4"
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

// loop
yash::token loop(const std::string& prompt=yash::PROMPT);


#define Black "\u001b[30m"
#define Red "\u001b[31m"
#define Green "\u001b[32m"
#define Yellow "\u001b[33m"
#define Blue "\u001b[34m"
#define Magenta "\u001b[35m"
#define Cyan "\u001b[36m"
#define White "\u001b[37m"
#define B_Black "\u001b[30;1m"
#define B_Red "\u001b[31;1m"
#define B_Green "\u001b[32;1m"
#define B_Yellow "\u001b[33;1m"
#define B_Blue "\u001b[34;1m"
#define B_Magenta "\u001b[35;1m"
#define B_Cyan "\u001b[36;1m"
#define B_White "\u001b[37;1m"
#define BG_Black "\u001b[40m"
#define BG_Red "\u001b[41m"
#define BG_Green "\u001b[42m"
#define BG_Yellow "\u001b[43m"
#define BG_Blue "\u001b[44m"
#define BG_Magenta "\u001b[45m"
#define BG_Cyan "\u001b[46m"
#define BG_White "\u001b[47m"
#define BG_B_Black "\u001b[40;1m"
#define BG_B_Red "\u001b[41;1m"
#define BG_B_Green "\u001b[42;1m"
#define BG_B_Yellow "\u001b[43;1m"
#define BG_B_Blue "\u001b[44;1m"
#define BG_B_Magenta "\u001b[45;1m"
#define BG_B_Cyan "\u001b[46;1m"
#define BG_B_White "\u001b[47;1m"
#define Bold "\u001b[1m"
#define Underline "\u001b[4m"
#define Reversed "\u001b[7m"
#define Up "\u001b[{n}A"
#define Down "\u001b[{n}B"
#define Right "\u001b[{n}C"
#define Left "\u001b[{n}D"
#define Reset "\u001b[0m"


#endif /* YASH_HH */

