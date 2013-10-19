#ifndef CHAPTER_17_TOKEN_HPP
#define CHAPTER_17_TOKEN_HPP

#include <string>
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

bool operator==(Token const& lhs, Token const& rhs);
bool operator!=(Token const& lhs, Token const& rhs);
std::ostream& operator<<(std::ostream& os, Token const& tok);

#endif
