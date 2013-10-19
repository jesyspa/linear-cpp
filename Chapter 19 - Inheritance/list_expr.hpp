#ifndef CHAPTER_19_LIST_EXPR_HPP
#define CHAPTER_19_LIST_EXPR_HPP

#include "expression.hpp"
#include <vector>
#include <memory>

/* We'd like our ListExpr to store a vector of expressions.  However, a vector
 * stores instances of the type it contains, and we want can't make an instance
 * of Expression -- nor do we want to, for that matter.  We'd like to be able to
 * put NumberExprs, VariableExprs, and ListExprs into whatever data structure we
 * use.
 *
 * In order to do this we introduce pointers.  We won't store the object itself:
 * instead we'll create an object somewhere and then store a pointer to it in
 * the vector.  You could see such a pointer as an iterator to a collection that
 * only has one element: it isn't the object itself, but we can access the
 * object through it.  Alternatively, you can see the pointer as a reference
 * which we can reassign at will.
 *
 * An important question that comes up is how we'll make sure the object we
 * create exists as long as we want it to, and no longer.  If we make a local
 * and then store a pointer to it, it will be destroyed once we exit the
 * function, and the pointer will be invalid.  On the other hand, we somehow
 * have to make sure that once we no longer have a use for the object, it gets
 * cleaned up.
 *
 * First, though, let's take a look at how to create an object.  For this
 * purpose we will use the std::make_shared function template.  For example,
 *
 *      std::make_shared<NumberExpr>(x)
 *
 * This will construct a NumberExpr with value x, and then return a pointer to
 * the object.  The pointer will have type std::shared_ptr<NumberExpr>, which
 * will be convertible to std::shared_ptr<Expression>.
 *
 * Apart from creating our object, make_shared will also create a counter for
 * the number of shared_ptrs that point to it.  Every time we copy a pointer
 * that counter will be incremented, while every time we destroy one it will be
 * decremented.  Once the counter reaches zero, our object will be destroyed;
 * this is what we want, as we don't want an object we can't access lying
 * around.
 *
 * Note that there are cases when objects become unreachable, but are kept
 * alive: if A has a shared_ptr to B, and B has a shared_ptr to A, neither will
 * be destroyed, even if the rest of our program cannot access them.
 *
 * Also note that seeing as shared_ptr handles the destruction of the object,
 * the object has to have been created in a way that is compatible with how it
 * destroys things.  This won't be a problem for us yet, as make_shared is the
 * only way we know to make pointers, but it's worth keeping in mind if you
 * experiment.
 */

class ListExpr : public Expression {
    // This may look strange, but is simply a vector of pointers to Expressions.
    std::vector<std::shared_ptr<Expression>> elements;

public:
    // We'll want to add expressions to the vector one by one.
    void add(std::shared_ptr<Expression> expr);

    void print(std::ostream& out) const override;
};

/* Now that we can represent the tree, let's make the parser create it.  Go on
 * to parser.hpp.
 */

#endif
