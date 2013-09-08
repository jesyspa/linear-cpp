#ifndef CHAPTER_15_LEX_HPP
#define CHAPTER_15_LEX_HPP

#include "token.hpp"
#include <istream>

/* Now that we've defined the Token type, we can use it like just about any
 * other kind of type.  It doesn't have all that many operations defined on it
 * yet -- we can copy and assign it, but not compare it, for instance -- but we
 * have enough to create them and return them from functions.
 */

// Instead of print_next_token we have an extract_next_token which reads a token
// and returns it.
//
// All other lexing functions are implementation details, so we don't declare
// them in the header.
Token extract_next_token(std::istream& stream);

#endif

