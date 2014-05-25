#ifndef CHAPTER_19_PARSER_HPP
#define CHAPTER_19_PARSER_HPP

#include "expression.hpp"
#include <istream>
#include <memory>

// Our function no longer does any printing, but it does need to return a
// pointer to the expression we parsed.
std::shared_ptr<Expression> parse_expression(std::istream& input);

/* Go on to parser.cpp.
 */

#endif
