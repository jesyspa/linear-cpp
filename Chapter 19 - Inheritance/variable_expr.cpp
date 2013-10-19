#include "variable_expr.hpp"

VariableExpr::VariableExpr(std::string const& name) : name(name) {}

void VariableExpr::print(std::ostream& out) const {
    out << name;
}
