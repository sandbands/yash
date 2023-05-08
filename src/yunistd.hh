/**
 * @file yunistd.hh
 * @author ARCO DEVELOPMENT (development.arco@gmail.com)
 * @brief Cross-platform solution to including unistd/windows header
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef YUNISTD_HH
#define YUNISTD_HH

#include "yash.hh"

#if PLATFORM_ID == PLATFORM_WINDOWS_ID
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

#endif /* YUNISTD_HH */
