#ifndef CHAPTER_16_LEX_HPP
#define CHAPTER_16_LEX_HPP

#include "token.hpp"
#include <istream>

Token extract_next_token(std::istream& stream);

#endif

