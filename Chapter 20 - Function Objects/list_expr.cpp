#include "list_expr.hpp"
#include "variable_expr.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>

void ListExpr::add(std::shared_ptr<Expression> expr) {
    elements.push_back(expr);
}

void ListExpr::print(std::ostream& out) const {
    out << '(';
    bool first = true;
    for (auto const& e : elements) {
        if (first)
            first = false;
        else
            out << ' ';
        e->print(out);
    }
    out << ')';
}

int ListExpr::evaluate(SymbolTable const& symbol_table) const {
    if (elements.empty())
        throw std::runtime_error{"evaluating empty list"};
    std::vector<int> args;
    // TODO: Comment on how this works.
    std::transform(std::begin(elements) + 1, std::end(elements), std::back_inserter(args), [&](std::shared_ptr<Expression> expr) { 
        return expr->evaluate(symbol_table);
    });

    auto& function_name = dynamic_cast<VariableExpr&>(*elements[0]);
    auto& function = symbol_table.at(function_name.get_name());
    return function(args);
}
