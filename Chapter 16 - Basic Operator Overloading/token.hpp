#ifndef CHAPTER_16_TOKEN_HPP
#define CHAPTER_16_TOKEN_HPP

#include <string>
#include <istream>
#include <ostream>

int const open_paren_token = 0;
int const close_paren_token = 1;
int const name_token = 2;
int const number_token = 3;
int const end_of_file_token = 4;

struct Token {
    int type;
    std::string value;
};

/* As token.hpp is a header file, we don't define the operator overloads yet.
 * However, we do want the other files to be aware of them, so we do need to
 * declare them.
 *
 * Treat the operator declarations just as function declarations with a funny
 * name.  You have less freedom when defining operators: for example, you can't
 * change the number of parameters willy-nilly, but the body may do anything a
 * function may do.
 */

bool operator==(Token const& lhs, Token const& rhs);
bool operator!=(Token const& lhs, Token const& rhs);
std::istream& operator>>(std::istream& is, Token& tok);
std::ostream& operator<<(std::ostream& os, Token const& tok);

/* Now go to token.cpp to see how things are implemented.
 */

#endif
