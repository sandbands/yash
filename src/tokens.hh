/**
 * @file tokens.hh
 * @author your name (you@domain.com)
 * @brief Tokens
 * @version 0.1
 * @date 2023-01-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef TOKENS_HH
#define TOKENS_HH

namespace yash {
	typedef enum token {
		TOK_SUCCESS,	// successful execution flow
		TOK_RESTART,	// restart calls
		TOK_EXIT,		// exit calls
		TOK_RETURN,		// return calls
		TOK_ERROR,		// errors
		TOK_FUNC,		// function calls
		TOK_BLANK,		// no input
		TOK_NONE,		// nothing
	};
}

#endif /* TOKENS_HH */
