#include "lex.hpp"
#include <cctype>
#include <stdexcept>

Token lex_name(std::istream& stream);
Token lex_number(std::istream& stream);
Token lex_operator(std::istream& stream);

bool isoperator(char c) {
    std::string const valid_chars = "+*-/!=<>";
    return valid_chars.find(c) != std::string::npos;
}

Token extract_next_token(std::istream& stream) {
    char c;
    while (stream.get(c) && std::isspace(c));

    if (!stream)
        return {end_of_file_token, ""};

    if (c == '(')
        return {open_paren_token, "("};
    if (c == ')')
        return {close_paren_token, ")"};

    stream.unget();

    if (std::isalpha(c))
        return lex_name(stream);
    if (std::isdigit(c))
        return lex_number(stream);
    if (isoperator(c))
        return lex_operator(stream);

    throw std::runtime_error{"unrecognised character"};
}

Token lex_name(std::istream& stream) {
    char c;
    std::string name;
    while (stream.get(c) && std::isalpha(c))
        name.push_back(c);

    if (stream)
        stream.unget();

    return {name_token, name};
}

Token lex_number(std::istream& stream) {
    char c;
    std::string number;
    while (stream.get(c) && std::isdigit(c))
        number.push_back(c);

    if (stream)
        stream.unget();

    return {number_token, number};
}

Token lex_operator(std::istream& stream) {
    char c;
    std::string op;
    while (stream.get(c) && isoperator(c))
        op.push_back(c);

    if (stream)
        stream.unget();

    return {name_token, op};
}

