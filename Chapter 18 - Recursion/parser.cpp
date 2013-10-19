#include "parser.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include <iostream>
#include <stdexcept>
#include <cassert>

// As we saw in the examples, and expression can contain another expression.
// We already have a function for parsing expressions, so we may as well use
// that for the subexpression, too.  We can't use parse_and_reprint_expression
// directly for this purpose, as we can't give it a lexer and indentation level,
// so we introduce a helper function that does track that data.
//
// We return bool to indicate whether parsing an expression succeded.  We don't
// throw an exception for that, as it isn't an error situation: when we're
// parsing the arguments to a function, at some point we'll run into the closing
// brace, which means we have all the arguments and continue.
bool p_expression(Lexer& lexer, int indent);

// Print the specified number of spaces.
void indent_to(int indent);

// Helper functions for printing.
void pretty_print_name(std::string const& name, int indent);
void pretty_print_number(std::string const& number, int indent);

void parse_and_reprint_expression(std::istream& input) {
    // Why bother with this function, if we could just let people call p_call?
    // Encapsulation.  This function specifies only that which is really
    // necessary: we need an istream to read input from.  Details like
    // indentation and the lexer are exactly that: details, and whoever is using
    // the parser likely won't care about them.  Splitting things this way makes
    // the calling code easier to understand.
    Lexer lexer(input);

    if (!lexer)
        throw std::runtime_error{"Invalid input: stream not in good state."};

    auto success = p_expression(lexer, 0);
    if (!success)
        throw std::runtime_error{"Invalid input: no expression found."};
}

/* When the lexer reaches the end of file, it will emit an eof token before
 * going into a bad state.  It would be convenient to check only for this token,
 * instead of also having to check the lexer state all the time.
 *
 * Unfortunately, there may be a bug in the code leading to one of these
 * functions being called when the eof has already been extracted.  If we don't
 * check the state, such a bug would lead to failures when we try to use the
 * values, which could happen significantly later than the read itself, and
 * which would likely be hard to fix.
 *
 * To detect such programmer errors, we can use the standard assert facility.
 * The syntax is like a function call:
 *
 *      assert(expression);
 *
 * If the expression evaluates to true, nothing happens.  However, if the
 * expression is false, the program will exit and an error message will be
 * displayed.
 *
 * assert may look like a function, but it isn't one.  There is, for example, a
 * way to disabling asserts, so that the statement is ignored entirely and the
 * expression is not evaluated at all.
 */

void indent_to(int indent) {
    for (int i = 0; i < indent; ++i)
        std::cout.put(' ');
}

void pretty_print_name(std::string const& name, int indent) {
    indent_to(indent);
    std::cout << "name: " << name << '\n';
}

void pretty_print_number(std::string const& number, int indent) {
    indent_to(indent);
    std::cout << "number: " << number << '\n';
}

// Parsing a function call involves quite a bit more work than other
// expressions, so we make a separate function for that.
void p_function_call(Lexer& lexer, int indent) {
    assert(lexer);

    indent_to(indent);
    std::cout << "function call:\n";

    indent_to(indent+4);
    std::cout << "function:\n";

    auto success = p_expression(lexer, indent+8);
    if (!success)
        throw std::runtime_error{"Invalid input: expected function."};

    indent_to(indent+4);
    std::cout << "arguments: \n";
    // The parsing already does everything we want, so we simply need to loop
    // until we have no more expressions.
    while (p_expression(lexer, indent+8));
}

bool p_expression(Lexer& lexer, int indent) {
    assert(lexer);

    auto token = lexer.extract();

    // First check for cases where there is no expression.
    if (token.type == end_of_file_token)
        throw std::runtime_error{"Invalid input: expected an expression."};

    if (token.type == close_paren_token)
        return false;

    // From here on, we know that if the token type is valid, the return value
    // will be true.
    if (token.type == name_token)
        pretty_print_name(token.value, indent);
    else if (token.type == number_token)
        pretty_print_number(token.value, indent);
    else if (token.type == open_paren_token)
        p_function_call(lexer, indent);
    else
        throw std::logic_error{"Unrecognised token type."};

    return true;
}

/* We've now implemented a very simple parser!  Note that the way we're doing
 * things is hardly optimal.  For one, we're mixing code does that parsing with
 * code that does output.  This is ugly, but means we can get the parsing logic
 * written before we look at the features necessary to store the program that we
 * parsed.  Take a look at main.cpp, where we use the parser.
 */

