#ifndef CHAPTER_18_PARSER_HPP
#define CHAPTER_18_PARSER_HPP

#include <istream>

/* This header can be extremely simple.  Unlike in the case of a Lexer, we don't
 * need to give the parser observable state.  Thanks to this, a simple function
 * will do, and so we only expose that, leaving the details to the
 * implementation.
 */

// Read an expression and re-print it in a pretty way.
void parse_and_reprint_expression(std::istream& input);

/* Continue to parser.cpp to see how we implement this.
 */

#endif
