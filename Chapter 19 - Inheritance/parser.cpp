#include "parser.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include "expression.hpp"
#include "number_expr.hpp"
#include "variable_expr.hpp"
#include "list_expr.hpp"
#include <iostream>
#include <stdexcept>
#include <cassert>

// Here too we'll return the parsed expression.  Note that we aren't returning a
// bool.  Instead, we'll use the fact that we can have a pointer pointing to
// nothing.  p_expression will return a pointer to the parsed expression if
// there is one, or a so-called null pointer if there isn't.
std::shared_ptr<Expression> p_expression(Lexer& lexer);

std::shared_ptr<Expression> parse_expression(std::istream& input) {
    Lexer lexer(input);

    if (!lexer)
        throw std::runtime_error{"Invalid input: stream not in good state."};

    auto expr = p_expression(lexer);
    if (!expr)
        throw std::runtime_error{"Invalid input: no expression found."};

    return expr;
}

std::shared_ptr<Expression> p_function_call(Lexer& lexer) {
    assert(lexer);

    auto list = std::make_shared<ListExpr>();

    while (auto ptr = p_expression(lexer))
        list->add(ptr);

    return list;
}

std::shared_ptr<Expression> p_expression(Lexer& lexer) {
    assert(lexer);

    auto token = lexer.extract();

    if (token.type == end_of_file_token)
        throw std::runtime_error{"Invalid input: expected an expression."};

    if (token.type == close_paren_token)
        return {};

    if (token.type == name_token)
        return std::make_shared<VariableExpr>(token.value);
    if (token.type == number_token)
        return std::make_shared<NumberExpr>(std::stoi(token.value));
    if (token.type == open_paren_token)
        return p_function_call(lexer);

    throw std::logic_error{"Unrecognised token type."};
}

/* Notice how much simpler the parsing code became now that we don't have to
 * worry about printing at the same time.
 *
 * With this out of the way, let's implement the printing.  We'll go for a
 * simpler format than in the previous chapter; feel free to expand it as an
 * exercises.
 *
 * Next is number_expr.cpp.
 */
