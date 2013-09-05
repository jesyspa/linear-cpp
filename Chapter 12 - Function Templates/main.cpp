/* Suggested order: main.cpp (beginning), vector_algos.hpp, main.cpp (end)
 *
 * In this chapter we'll take a look at templates.  We won't cover them entirely
 * right away; templates have some very advanced features that we don't
 * currently have a use for.  However, the basic uses are already applicable,
 * and so we'll take a brief look at those.
 *
 * Functions allow us to generalise code over values; templates allow us to
 * generalise code over types.
 *
 * In the last few chapters we wrote many functions that worked on vectors of
 * ints.  We'll now use templates to allow us to work over many types.
 *
 * By the way, even though we are only now writing our own templates, we've
 * already used many that the standard library has provided us with.  The
 * only explicit use was std::vector, where we could provide the type of the
 * elements we'd like to store.  We could use std::vector<int>, or
 * std::vector<double>, or even std::vector<std::vector<std::string>>, while the
 * programmers of the standard library only had to write std::vector once.
 *
 * (In practice, they may have written specialised options to improve
 * performance in some cases.  There is also std::vector<bool>, which the
 * standard insists be a little different.)
 *
 * Apart from that, all of the standard algorithms we used in the last chapter
 * were actually templates.  We could pretend they were just functions because
 * the compiler could figure out what types we wanted to use them on from the
 * arguments we passed.  We'll keep using that feature in this chapter, though
 * there'll be a few places we have to explicitly specify the types anyway.
 *
 * Take a look at vector_algos.hpp now, and come back to look at main once
 * you've seen how templates are implemented.
 */
#include "vector_algos.hpp"
#include <iostream>
#include <algorithm>

int main() {
    // Welcome back.  As you can see, our main function is almost undisturbed,
    // except that we have read_vector<int> instead of read_int_vector.  Does
    // the program still work if you change int to double?  What about to
    // std::string?
    std::cout << "Enter at least one number:\n";
    auto v = read_vector<int>();

    if (v.empty()) {
        std::cout << "I said, at least one number.\n";
        return -1;
    }

    std::cout << "Sum: " << sum(v) << "\n";
    std::cout << "Average: " << average(v) << "\n";

    auto sorted_v = sort(v);

    // Let's add a function that lets us display a range.
    std::cout << "Your input, sorted: ";
    display_range(sorted_v.begin(), sorted_v.end());
    std::cout << "\n";
}

/* That's all we'll cover about templates for now.  There is much, much more to
 * see, but it isn't relevant yet.  The next chapter is going to be about
 * handling errors.
 *
 * The next big topic is going to be classes, and that's going to take quite a
 * few chapters.  I find that covering classes in isolation makes it hard to
 * grasp why you'd use them.  Starting from the lesson after next, we'll be
 * working on building a larger program, where we'll be applying a mix of
 * everything we've learned so far.
 */
