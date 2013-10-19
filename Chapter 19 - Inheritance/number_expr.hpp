#ifndef CHAPTER_19_NUMBER_EXPR_HPP
#define CHAPTER_19_NUMBER_EXPR_HPP

#include "expression.hpp"

// This is the syntax for defining NumberExpr as a derived class of Expression.
// The public means that everyone can see this relationship: had we put private,
// then only NumberExpr would know that it derives from Expression.
class NumberExpr : public Expression {
    // The representation of a NumberExpr is simple: we just store the number.
    int value;

public:
    // We require that a NumberExpr be created with a value.  Adding this
    // constructor means that a default one is not auto-generated, but this is
    // okay: we want every NumberExpr to have a value, anyway.
    NumberExpr(int value);

    // We want to make instances of NumberExpr, so we have to override print.
    // By using the override keyword we tell the compiler that we really do want
    // an override, not an overload; if there was no function in Expression that
    // our print overrides, we would get a compiler error.
    //
    // Notice that we don't specify virtual here.  We could if we wanted, and it
    // would not change anything: as the base class made it virtual, it will
    // automatically be virtual in all derived classes.
    void print(std::ostream& out) const override;
};

/* variable_expr.hpp is next, and almost the same as this file.
 */

#endif
