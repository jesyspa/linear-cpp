#include "token.hpp"

bool operator==(Token const& lhs, Token const& rhs) {
    return lhs.type == rhs.type && lhs.value == rhs.value;
}

bool operator!=(Token const& lhs, Token const& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, Token const& tok) {
    os << "{ ";

    if (tok.type == open_paren_token)
        os << "open_paren_token";
    else if (tok.type == close_paren_token)
        os << "close_paren_token";
    else if (tok.type == name_token)
        os << "name_token";
    else if (tok.type == number_token)
        os << "number_token";
    else if (tok.type == end_of_file_token)
        os << "end_of_file_token";

    os << ", \"" << tok.value << "\" }";
    return os;
}
