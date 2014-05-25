#ifndef CHAPTER_20_LIST_EXPR_HPP
#define CHAPTER_20_LIST_EXPR_HPP

#include "expression.hpp"
#include <vector>
#include <memory>

class ListExpr : public Expression {
    std::vector<std::shared_ptr<Expression>> elements;

public:
    void add(std::shared_ptr<Expression> expr);

    void print(std::ostream& out) const override;

    int evaluate(SymbolTable const& symbol_table) const override;
};

#endif
