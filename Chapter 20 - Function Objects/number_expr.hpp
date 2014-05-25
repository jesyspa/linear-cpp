#ifndef CHAPTER_20_NUMBER_EXPR_HPP
#define CHAPTER_20_NUMBER_EXPR_HPP

#include "expression.hpp"

class NumberExpr : public Expression {
    int value;

public:
    NumberExpr(int value);

    void print(std::ostream& out) const override;

    int evaluate(SymbolTable const& symbol_table) const override;
};

#endif
