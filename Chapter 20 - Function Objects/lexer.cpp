#include "lexer.hpp"
#include <cctype>
#include <stdexcept>

bool isoperator(char c) {
    std::string const valid_chars = "+*-/!=<>";
    return valid_chars.find(c) != std::string::npos;
}

Lexer::Lexer(std::istream& is) : input_stream(is) {}

Token Lexer::extract() {
    ignore_whitespace();

    char c;
    if (!peek(c))
        return {end_of_file_token, ""};

    if (std::isalpha(c))
        return lex_name();
    if (std::isdigit(c))
        return lex_number();
    if (isoperator(c))
        return lex_operator();

    ignore();

    if (c == '(')
        return {open_paren_token, "("};
    if (c == ')')
        return {close_paren_token, ")"};

    throw std::runtime_error{"unrecognised character"};
}

Lexer::Position Lexer::get_position() const {
    return current_position;
}

Lexer::operator bool() const {
    return bool(input_stream);
}

bool Lexer::peek(char& c) const {
    int x = input_stream.peek();
    if (x == std::char_traits<char>::eof())
        return false;
    c = x;
    return true;
}

void Lexer::ignore() {
    char c;
    if (!peek(c))
        throw std::logic_error{"ignoring past end of file"};
    input_stream.ignore();
    if (c == '\n') {
        current_position.line += 1;
        current_position.column = 1;
    } else {
        current_position.column += 1;
    }
}

bool Lexer::get(char& c) {
    if (!peek(c))
        return false;
    ignore();
    return true;
}

void Lexer::ignore_whitespace() {
    char c;
    while (peek(c) && std::isspace(c))
        ignore();
}

Token Lexer::lex_name() {
    char c;
    std::string name;
    while (peek(c) && std::isalpha(c)) {
        name.push_back(c);
        ignore();
    }

    return {name_token, name};
}

Token Lexer::lex_number() {
    char c;
    std::string number;
    while (peek(c) && std::isdigit(c)) {
        number.push_back(c);
        ignore();
    }

    return {number_token, number};
}

Token Lexer::lex_operator() {
    char c;
    std::string op;
    while (peek(c) && isoperator(c)) {
        op.push_back(c);
        ignore();
    }

    return {name_token, op};
}

bool operator!(Lexer const& lex) {
    return !bool(lex);
}

bool operator==(Lexer::Position lhs, Lexer::Position rhs) {
    return lhs.line == rhs.line && lhs.column == rhs.column;
}

bool operator!=(Lexer::Position lhs, Lexer::Position rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, Lexer::Position pos) {
    os << "(line: " << pos.line << ", column:" << pos.column << ")";
    return os;
}
