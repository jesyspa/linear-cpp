#include "variable_expr.hpp"
#include <stdexcept>

VariableExpr::VariableExpr(std::string const& name) : name(name) {}

void VariableExpr::print(std::ostream& out) const {
    out << name;
}

int VariableExpr::evaluate(SymbolTable const&) const {
    throw std::runtime_error{"variables are not yet supported"};
}

std::string VariableExpr::get_name() const {
    return name;
}
