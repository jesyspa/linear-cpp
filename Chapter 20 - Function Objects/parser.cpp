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

