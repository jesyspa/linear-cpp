#ifndef CHAPTER_19_LEXER_HPP
#define CHAPTER_19_LEXER_HPP

#include "token.hpp"
#include <istream>
#include <ostream>
#include <string>

struct Lexer {
    explicit Lexer(std::istream& is);
    Lexer(Lexer const&) = delete;

    Token extract();

    struct Position {
        int line, column;
    };

    Position get_position() const;

    explicit operator bool() const;

private:
    std::istream& input_stream;

    Position current_position{1, 1};

    bool peek(char& c) const;

    void ignore();

    bool get(char& c);

    void ignore_whitespace();

    Token lex_name();
    Token lex_number();
    Token lex_operator();
};

bool operator!(Lexer const& lex);

bool operator==(Lexer::Position lhs, Lexer::Position rhs);
bool operator!=(Lexer::Position lhs, Lexer::Position rhs);
std::ostream& operator<<(std::ostream& os, Lexer::Position pos);

#endif
