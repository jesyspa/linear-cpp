#include "list_expr.hpp"

void ListExpr::add(std::shared_ptr<Expression> expr) {
    elements.push_back(expr);
}

void ListExpr::print(std::ostream& out) const {
    // Ignoring the extra trouble done to not print the trailing space, this is
    // surprisingly straightforward code.  We don't need to check the types of
    // anything; we can simply use the virtual print function and it'll do the
    // right thing depending on the type of the element.
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

/* Now let's take a look at how it all fits together in main.cpp.
 */
