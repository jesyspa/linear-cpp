#ifndef CHAPTER_20_VARIABLE_EXPR_HPP
#define CHAPTER_20_VARIABLE_EXPR_HPP

#include "expression.hpp"
#include <string>

class VariableExpr : public Expression {
    std::string name;

public:
    VariableExpr(std::string const& name);

    void print(std::ostream& out) const override;

    int evaluate(SymbolTable const& symbol_table) const override;

    std::string get_name() const;
};

#endif
