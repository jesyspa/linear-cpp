#include "lexer.hpp"
#include <cctype>
#include <stdexcept>

// We keep this helper function around: it doesn't need any class data so it
// doesn't make sense to make it a member function.
bool isoperator(char c) {
    std::string const valid_chars = "+*-/!=<>";
    return valid_chars.find(c) != std::string::npos;
}

/* We need to define all those functions we declared Lexer to have.  We again
 * use the scope resolution operator, now to specify that we are indeed defining
 * a member function of Lexer, not a normal function of the same name.
 */

// We've already initialized current_position, so we don't have to do anything
// about that in our constructor.  On the other hand, we get the value for
// input_stream from a parameter, and we'd like to initialize it.  Furthermore,
// being a reference, input_stream cannot be default-constructed, and so we use
// the constructor-initializer.  (Even if we could have used an assignment, a
// constructor-initializer is neater, and may be faster.)
Lexer::Lexer(std::istream& is) : input_stream(is) {}
// The : starts the constructor-initializer, then input_stream(is) binds
// input_stream to is, and finally {} is the empty constructor body.

// This function looks much like extract_next_token.  However, we don't have to
// pass the stream around explicitly; instead, we can use input_stream from any
// of our member functions.  When inside a member function, calling another
// member function without specifying what instance we are calling it on calls
// it on the current instance.
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
    // Here we again use the function-like form of conversion.  This is because
    // operator bool() in std::istream is also explicit, and so simply returning
    // would give us an error.
    return bool(input_stream);
}

bool Lexer::peek(char& c) const {
    // std::istream doesn't allow us to peek(c) like it allowed us to get(c), so
    // we have to work around this.

    // peek returns an int, so that we can check for end-of-file.
    int x = input_stream.peek();
    // std::char_traits<char>::eof returns the value that indicates an end of file.
    if (x == std::char_traits<char>::eof())
        return false;
    // Otherwise, the implicit conversion is guaranteed to be safe.
    c = x;
    return true;
}

// ignore is where the work regarding position tracking happens.  This isn't the
// most efficient way of implementing a Lexer; we almost always call peek double
// the number of times necessary.  However, at this point the gain in safety is
// worth the drop in performance.
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

/* With the lexer implemented, let's look at the resulting main function.
 */
