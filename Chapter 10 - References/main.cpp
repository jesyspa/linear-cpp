/* Suggested reading order: main.cpp, vector_algos.hpp, vector_algos.cpp
 *
 * Now that we've seen a few functions, we're going to come back and fix the
 * main performance issue we spotted: the fact we're passing vectors by value
 * everywhere, causing a significant amount of copying to happen.
 *
 * When we say "a copy is made", we mean that the original value is read from
 * but not modified in any way.  The function only deals with this copy, and any
 * changes it makes aren't visible; we could see that in the sort example in the
 * last chapter.
 *
 * We could rewrite all our functions to take iterator pairs, and there are some
 * good reasons to do that.  However, it is not always the most convenient
 * solution; for example, taking the sum of a filtered vector would require that
 * we store the result of filter_greater_than, instead of directly passing it to
 * sum.
 *
 * Instead we'll use references.  These provide a way to give a value a
 * different name.  For now, we can limit ourselves to so-called "lvalue
 * references"; there are other kinds, where the rules are different.
 *
 * Enough.  Let's dive into a function and look at some examples.
 */

#include <iostream>

// Recall that void means the function will not return anything.
void reference_practice() {
    // I'll step aside from my usual system of introducing practical examples
    // for now.  References are mostly used for parameters and return values,
    // but the basic mechanics are easier to demonstrate within one function.

    // If we want to make another name for something, we need to have that
    // something first.  Let's use x for this example.
    int x = 5;

    // The type "reference to int" is written as int&.  We say that the
    // reference y is bound to x.  This can only be done when we define y; from
    // this point onwards, y and x are going to behave the same way.
    // Conversely, we have to bind y to something; an unbound reference would be
    // useless, and is thus forbidden.
    int& y = x;

    // (Later on, when we learn how to inspect the declared types of x and y,
    // we'll be able to see a few differences.  Those aren't worth worrying
    // about yet; you can treat y and x as the same.)

    std::cout << "int x = 5;\n";
    std::cout << "int& y = x;\n";
    std::cout << ">  x == " << x << "\n";
    std::cout << ">  y == " << y << "\n";

    // Let's try assigning something to y:
    y = 2;
    std::cout << "y = 2;\n";
    std::cout << ">  x == " << x << "\n";
    std::cout << ">  y == " << y << "\n";

    // Let's assign something to x now:
    x = 3;
    std::cout << "x = 3;\n";
    std::cout << ">  x == " << x << "\n";
    std::cout << ">  y == " << y << "\n";

    // No matter what we do, x and y will have the same value.

    // A reference to a reference doesn't make sense.  We can bind an int& to y,
    // but it will have the same effect as binding it to x.

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

    // Note also that auto assumes your variable shouldn't be a reference unless
    // you explicitly tell it otherwise:
    auto z1 = y;
    auto& z2 = y;

    // The compiler will auto-detect the type for z2, assuming that it has to be
    // a reference type.  Such "partial detection" is only possible for a few
    // cases.

    x = 8;

    std::cout << "auto z1 = y;\n";
    std::cout << "auto& z2 = y;\n";
    std::cout << "x = 8;\n";
    std::cout << ">  z1 == " << z1 << "\n";
    std::cout << ">  z2 == " << z2 << "\n";

    // Now let's look at how it works with functions.  By the way, we can
    // declare functions inside other functions, but we can't define them.
    void takes_a_reference(int& i);

    std::cout << "\n"; // newline for readability.

    // takes_a_reference takes an int by reference.  No copy will be made
    // (though for an int, this is minor), and the value may change.
    std::cout << ">  x == " << x << "\n";
    std::cout << "takes_a_reference(x);\n";
    takes_a_reference(x);
    std::cout << ">  x == " << x << "\n";

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
    std::cout << "\n";
    std::cout << "int const& c = x;\n";

    // Note that even though we can't change x via c, we can change c via x!
    std::cout << ">  c == " << c << "\n";
    x = 5;
    std::cout << "x = 5;\n";
    std::cout << ">  c == " << c << "\n";

    // Now let's see what it looks like when we're dealing with functions:
    void takes_a_reference_to_const(int const& i);

    std::cout << "\n";
    std::cout << ">  x == " << x << "\n";
    takes_a_reference_to_const(x);
    std::cout << "takes_a_reference_to_const(x);\n";
    std::cout << ">  x == " << x << "\n";

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
    std::cout << "\n";
    void print(std::string const& str);
    // What's the \"?  We can't have a " in the string, as that would end the
    // string.  The \" is turned into a ".
    std::cout << "print(\"I'm a string literal, not a string, but I can be converted!\");\n";
    print("I'm a string literal, not a string, but I can be converted!");

    // This is extremely convenient and the intended use of this rule.  On the
    // other hand...

    std::cout << "\n";
    std::cout << "double const& d = x;\n";
    double const& d = x;
    std::cout << ">  x == " << x << "\n";
    std::cout << ">  d == " << d << "\n";
    x = 13;
    std::cout << "x = 13;\n";
    std::cout << ">  x == " << x << "\n";
    std::cout << ">  d == " << d << "\n";
    // here, d is not a reference to x!  A reference to a double, even if it is
    // a double const, cannot reference an int!  Instead, a temporary was
    // created and d refers to that.

    /* This brings us to another very important issue.  We saw in the last
     * chapter that temporaries don't live very long.  How come this was okay?
     *
     * When a reference is bound to a temporary, that temporary is rescued from
     * immenent doom and will live as long as the reference bound to it does.
     *
     * Note that this extension is only granted to temporaries.  A reference to
     * non-const cannot be bound to a temporary, so it can never perform such
     * extension.  Furthermore, binding a reference to a reference will not
     * extend the lifetime further.  You cannot repeat this trick; trying to do
     * so will cause unpredictable and probably unpleasant results.
     *
     * For a similar reason, returning references to values is something that
     * has to be done with some care.  Had the return type of this function been
     * int&, we could have said "return x;" and returned a reference to x.
     * However, x would be destroyed when we left the function and the reference
     * would not refer to anything meaningful.  It's roughly the same situation
     * as if we returned an iterator into a vector that we defined in this
     * function.
     *
     * Note that lifetime extension cannot help here; it does not work for
     * return values.
     *
     * As with iterators, be careful about taking references to things that may
     * outlive the reference.  In particular, although returning references is
     * often very useful, make sure that it is also legal.
     */
}

// Some helper functions to illustrate the points above.  Play around with them
// to see what is and isn't allowed.
void takes_a_reference(int& i) {
    std::cout << ">  i == " << i << "\n";
    i = 7;
    std::cout << "i = 7;\n";
}

void takes_a_reference_to_const(int const& i) {
    std::cout << ">  i == " << i << "\n";
}

void print(std::string const& str) {
    std::cout << ">  str == \"" << str << "\"\n";
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
    auto v = sort(read_int_vector());

    std::cout << "You entered:";
    for (auto e : v)
        std::cout << " " << e;
    std::cout << "\n";

    // Search for a few numbers amongst those the user entered.
    for (int i = 0; i < 50; i += 5) {
        auto it = binary_search(v, i);
        if (it == v.end())
            std::cout << i << " was not amongst the numbers you entered.\n";
        else
            std::cout << "You entered " << (it - v.begin()) << " numbers less than " << i << ".\n";
    }

    std::cout << "Average: " << average(v) << "\n";
    std::cout << "Sum: " << sum(v) << "\n";

    std::cout << "Elements greater than 5:";
    for (auto e : filter_greater_than(v, 5))
        std::cout << " " << e;
    std::cout << "\n";
}
