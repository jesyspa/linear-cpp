#include "number_expr.hpp"

NumberExpr::NumberExpr(int value) : value(value) {}

// Implementing an override looks just like implementing a normal member function.
void NumberExpr::print(std::ostream& out) const {
    out << value;
}

/* variable_expr.cpp looks exactly the same, except for names, so feel free to
 * skip to list_expr.cpp.
 */
