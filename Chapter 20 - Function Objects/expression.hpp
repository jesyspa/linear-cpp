#ifndef CHAPTER_20_EXPRESSION_HPP
#define CHAPTER_20_EXPRESSION_HPP

#include "symbol_table.hpp"
#include <ostream>

struct Expression {
    virtual void print(std::ostream& out) const = 0;

    virtual int evaluate(SymbolTable const& symbol_table) const = 0;

    virtual ~Expression() = default;
};

inline std::ostream& operator<<(std::ostream& os, Expression const& expr) {
    expr.print(os);
    return os;
}

#endif
