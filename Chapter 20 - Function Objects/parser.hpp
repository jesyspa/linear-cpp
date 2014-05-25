#ifndef CHAPTER_20_PARSER_HPP
#define CHAPTER_20_PARSER_HPP

#include "expression.hpp"
#include <istream>
#include <memory>

std::shared_ptr<Expression> parse_expression(std::istream& input);

#endif
