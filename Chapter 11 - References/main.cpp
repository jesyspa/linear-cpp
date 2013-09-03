/* Suggested reading order: main.cpp, vector_algos.hpp, vector_algos.cpp
 *
 * Now that we've made our code much neater, we're going to solve the main
 * performance issue we spotted when writing this code: the fact we're copying
 * vectors all over the place.
 *
 * At the moment, we are passing our vectors by value.  That means that what the
 * function receives is a copy of the original vector.  The original vector is
 * inspected to make the copy, but its value does not change in any way.  What
 * we'd like to do here is, instead of passing the value of the vector, make the
 * parameter name simply another name for the vector we already have.
 *
 * The way to do this is with references.  For now, we're only going to look at
 * the references called "lvalue references"; later we'll cover a different kind
 * called "rvalue references", where the rules are slightly different.
 *
 * Enough.  Let's dive into a function and look at some examples.
 */

#include <iostream>

// Recall that void means the function will not return anything.
void reference_practice() {
    // If we want to make another name for something, we need to have that
    // something first.
    int x = 5;

    // The type "reference to int" is written as int&.
    int& y = x;

    // Note that we are not allowed to skip the initialisation of y like we
    // could have skipped it of x.  When we define a reference, we are creating
    // another name for something: we cannot delay specifying what it is another
    // name for.  We say that we have "bound (the reference) y to x".

    std::cout << "  references to x and y:\n";
    std::cout << "initially:\n";
    std::cout << "x = " << x << "\n";
    std::cout << "y = " << y << "\n";

    // Let's try assigning something to y:
    y = 2;
    std::cout << "after y = 2:\n";
    std::cout << "x = " << x << "\n";
    std::cout << "y = " << y << "\n";

    // Let's assign something to x now:
    x = 3;
    std::cout << "after x = 3:\n";
    std::cout << "x = " << x << "\n";
    std::cout << "y = " << y << "\n";

    // No matter what we do, x and y will have the same value.  They are the
    // same thing.  We will later see even more evidenence for this, though it
    // will take many more chapters.

    // Note that there is no way to make y be another name for a different
    // variable than x; until it is destroyed, it will remain loyal to what we
    // initialised it with.  You can create another reference to x, and it
    // doesn't matter whether you use x or y to create it:
    int& z1 = x;
    int& z2 = y;
    // x, y, z1, and z2 are all the same.  Later, when we have ways of observing
    // a variable's declared type, we will be able to note the difference, but
    // it isn't worth worrying about yet.

    /* By the way, remember how I said that if you have a "simple type" like
     * int, you can define multiple variables in one line by separating them
     * with a comma?  Well, C++ inherited certain rules from C, and those made
     * sense at the time...  put simply, int& is no longer simple enough for
     * this to be true.  For example, had we said
     *
     *      int& z1 = x, z2 = y;
     *
     * only z1 would be a reference, and z2 would not be.  I will have an
     * appendix on how these rules work exactly; fortunately, we'll soon see a
     * workaround that lets us turn any type into a "simple type".  For now,
     * when in doubt, write things out on their own line.
     *
     * (As a bonus, you can define both an int& and an int in a for loop
     * initialisation; don't expect to make many friends that way, though.)
     */

    std::cout << "z1 = " << z1 << "\n";
    std::cout << "z2 = " << z2 << "\n";

    // Now let's look at how it works with functions.  By the way, we can
    // declare functions inside other functions, but we can't define them.
    void takes_a_reference(int& i);

    std::cout << "\n  passing a reference:\n";

    // takes_a_reference takes an int by reference.  No copy will be made
    // (though for an int, this doesn't matter), and the value may change.
    std::cout << "x before we pass it: " << x << "\n";
    takes_a_reference(x);
    std::cout << "x after we pass it: " << x << "\n";

    /* Did x change?  Until you look at the definition of takes_a_reference, you
     * can't be sure.  We know that sum, average, and filter_greater_than
     * shouldn't be modifying the vectors we pass to them, though.  In fact,
     * we'd like to be able to provide a guarantee for that.
     *
     * C++ allows this to be done using const.  Just like int, int const is a
     * type.  It has all the same possible values that int has, but it doesn't
     * allow any operations that modify the value of a variable.  That means
     * that once we've defined it, we can't ever change it again.
     *
     * (Because of this, when working with const versions primitive types like
     * int, you have to initialise the value as soon as you define the variable:
     * there's no point if you don't!)
     *
     * A little bit about reading types: the best approximation is to read from
     * right to left.  An int const is a constant integer.  An int& is a
     * reference to an integer.  An int const& is a reference to a constant
     * integer.
     *
     * Because every int can be treated as an int const without any problems, we
     * can make an int const& refer to an int.  This lets us make a reference,
     * which means we avoid a copy, but we don't have to worry about our value
     * being changed.
     */

    // This is almost the same thing as our first example with y.  However,
    // this name for x doesn't let x be modified, while y does.  You could see
    // the difference as a drop in the amount of information: y knows that x is
    // actually mutable, this one doesn't.
    int const& c = x;
    std::cout << "\n  references to const:\n";

    // Note that even though we can't change x via c, we can change c via x!
    std::cout << "c = " << c << "\n";
    x = 5;
    std::cout << "c = " << c << "\n";

    // Now let's see what it looks like when we're dealing with functions:
    void takes_a_reference_to_const(int const& i);

    std::cout << "\n  passing a reference to const:\n";
    std::cout << "x before we pass it: " << x << "\n";
    takes_a_reference_to_const(x);
    std::cout << "x after we pass it: " << x << "\n";

    // Now we know that x did not change (unless someone has been doing some
    // very, very nasty things).

    /* What about an int& const?  That won't work.  It doesn't make sense for a
     * reference to be constant: we already can't change what it's an alias for,
     * and whether we can change the value it refers to is determined by the
     * inner const.  Because of this, int& const is an error.
     */

    /* Another good question is: what can we make references to?  It turns out
     * that the answer is not all that simple.
     *
     * First of all: if we have a named variable, we can always take a reference
     * to it.  Furthermore, if a function returns a reference, we can make a
     * reference to it.  Those are the two basic cases.
     *
     * When dealing with references to const types, we have a little more
     * freedom: we can take a reference to const to just about anything that is
     * of the same type.  If we take a reference to something that isn't of the
     * same type but is convertible to it, a temporary will be created and you
     * will get a reference to that.
     */

    // That last part has some surprising implications that you have to keep in
    // mind.  On the one hand, it means we can do the following:
    std::cout << "\n  binding to a temporary:\n";
    void print(std::string const& str);
    print("I'm a char literal, not a string, but I can be converted!");

    // This is extremely convenient and the intended use of this rule.  On the
    // other hand...
    double const& d = x;
    std::cout << "\n  doubles and ints:\n";
    std::cout << "before we modify x\n";
    std::cout << "x = " << x << "\n";
    std::cout << "d = " << d << "\n";
    x = 13;
    std::cout << "after we modify x\n";
    std::cout << "x = " << x << "\n";
    std::cout << "d = " << d << "\n";
    // here, d is not a reference to x!  A reference to a double, even if it is
    // a double const, cannot reference an int!  Instead, a temporary was
    // created and d refers to that.

    /* This brings us to another very important issue.  That temporary was,
     * well, temporary.  Temporaries are normally destroyed at the end of the
     * statement they occur in.  Whatever happened there that we can still
     * access it?
     *
     * When a reference to const is bound to a temporary, that temporary is
     * rescued from immenent doom and will live as long as the reference to
     * const does.  (There are a few exceptions, which we will see in due time.)
     *
     * Note that this extension is only granted to temporaries.  Therefore, a
     * reference to non-const cannot perform this extension.  Furthermore,
     * taking a reference to const of a reference to const will not extend the
     * lifetime further.  You cannot repeat this trick; trying to do so will
     * cause unpredictable and probably unpleasant results.
     *
     * For a similar reason, returning references to values is something that
     * has to be done with some care.  Had the return type of this function been
     * int&, we could have said "return x;" and returned a reference to x.
     * However, x would be destroyed when we left the function and the reference
     * would not refer to anything meaningful.
     *
     * If we made the return type int const&, we could again say "return x;",
     * but the result would not be any different: the lifetime would not be
     * extended, and accessing the value would have equally unpredictable
     * results.
     *
     * The moral of the story is that once references come into play, you should
     * be careful about how long you know things will live for.  Passing
     * parameters by reference is safe; returning values by reference is often
     * useful but requires a firm understanding of what is going on.
     */
}

// Some helper functions to illustrate the points above.  Play around with them
// to see what is and isn't allowed.
void takes_a_reference(int& i) {
    std::cout << "got a reference to an int: " << i << "\n";
    i = 7;
}

void takes_a_reference_to_const(int const& i) {
    std::cout << "got a reference to a const int: " << i << "\n";
}

void print(std::string const& str) {
    std::cout << str << "\n";
}

// Now that we've covered the theory, we can look at how it relates to our
// vector algorithms.
#include "vector_algos.hpp"

int main() {
    // Lets you see the results and experiment.
    reference_practice();
    std::cout << "\n"; // a newline to make it easier on the eyes

    std::cout << "Enter as many numbers as you want:\n";
    auto v = read_int_vector();

    std::cout << "Average: " << average(v) << "\n";
    std::cout << "Sum: " << sum(v) << "\n";

    std::cout << "Elements greater than 5:";
    for (auto e : filter_greater_than(v, 5))
        std::cout << " " << e;
    std::cout << "\n";

    return 0;
}
