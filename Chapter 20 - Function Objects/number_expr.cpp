#include "number_expr.hpp"

NumberExpr::NumberExpr(int value) : value(value) {}

void NumberExpr::print(std::ostream& out) const {
    out << value;
}

int NumberExpr::evaluate(SymbolTable const&) const {
    return value;
}
