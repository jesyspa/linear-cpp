#ifndef CHAPTER_19_EXPRESSION_HPP
#define CHAPTER_19_EXPRESSION_HPP

#include <ostream>

// The basic syntax for defining the expression class is the same.
struct Expression {
    // There's two things here that we haven't seen before.
    //
    // First of all, the function is prefixed with virtual.  This means that the
    // function may be overriden by a derived class.  If we have a NumberExpr
    // class that derives from Expression, and a reference to Expression that
    // actually refers to a NumberExpr object, a lookup will be done at runtime,
    // and the override defined in NumberExpr will be called instead.  Had the
    // function not been virtual, the print defined in Expression would be
    // called.
    //
    // Secondly, we have the = 0 at the end.  This means that print is a pure
    // virtual function: it does not have to be defined in Expression.  On the
    // other hand, it also means that we cannot create an instance of
    // Expression.  If we want to create an Expression, we have to make a
    // derived type, define an override for print, and then create an instance
    // of that.
    //
    // How is Expression still useful?  We can still make references to it.
    // Take a look at the operator>> defined below for an example.
    virtual void print(std::ostream& out) const = 0;

    // One of the things we'd like to be able to do with Expressions is to
    // destroy them; if we kept them around forever, we'd be using much more
    // memory than we really need.  Sometimes, we'll want to destroy an
    // Expression without knowing what kind of Expression it is.
    //
    // Whenever an object is destroyed, the destructor is run.  If we want to be
    // able to destroy objects as above, we must make the destructor virtual.
    // In this case, that's the only thing we need to change, so we can give it
    // the default implementation.
    virtual ~Expression() = default;
};

// Let's take a look at an example use of Expression.  We know that expr is
// going to be a reference to an object of some derived type.  We also know that
// that type must implement print for there to be an instance of it.  We can
// thus conclude that this is safe, but we can't know which version will be
// called until runtime -- and that's by design.
inline std::ostream& operator<<(std::ostream& os, Expression const& expr) {
    expr.print(os);
    return os;
}

/* Go on to number_expr.hpp.
 */

#endif
