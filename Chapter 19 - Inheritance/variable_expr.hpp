#ifndef CHAPTER_19_VARIABLE_EXPR_HPP
#define CHAPTER_19_VARIABLE_EXPR_HPP

#include "expression.hpp"
#include <string>

class VariableExpr : public Expression {
    std::string name;

public:
    VariableExpr(std::string const& name);

    void print(std::ostream& out) const override;
};

/* Now take a look at list_expr.hpp, which is significantly more interesting.
 */

#endif
