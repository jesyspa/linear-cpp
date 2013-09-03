/* We've already used functions in a number of different ways.  We were able to
 * get rid of some code duplication by using a function in several different
 * places; we were also able to make our code clearer by moving parts out into
 * functions of their own, and only having to mention their name.
 *
 * Now we will look at another benefit functions can have: they make it easy for
 * us to use code others have written.  As an example, we're going to rewrite
 * our sum function to use a standard functions.  We're also going to write a
 * few new functions.
 *
 * Before we get to that, though, there's a number of standard algorithms that
 * we can use directly from main.
 */

#include "vector_algos.hpp"
#include <iostream>
#include <algorithm>

// Let's define an alternative rule for comparing ints.  Instead of comparing
// them directly, we'll compare their values squared.  custom_comparison will
// return true for all x which are strictly less than y according to these
// rules.
bool custom_comparison(int x, int y) {
    return x*x < y*y;
}

int main() {
    std::cout << "Enter at least one number:\n";
    auto v = read_int_vector();

    // We don't want to have to write special cases for empty everywhere, so
    // let's terminate the program if that happens.
    if (v.empty()) {
        std::cout << "I said, at least one number.\n";
        return -1;
    }

    // std::max_element takes an iterator range and returns an iterator to the
    // greatest element.  Note that we can dereference the iterator safely here;
    // why?  How long will what it points to exist for?
    std::cout << "Maximum element: " << *std::max_element(v.begin(), v.end()) << "\n";

    // Minimum element is similar.  However, let's use our custom comparison
    // function.  Both max_element and min_element allow us to pass it as a
    // third argument.  If we don't, they assume we want comparison using the <
    // operator.
    std::cout << "Minimum element (normal): "
        << *std::min_element(v.begin(), v.end()) << "\n";
    std::cout << "Minimum element (custom comparison): "
        << *std::min_element(v.begin(), v.end(), custom_comparison) << "\n";

    std::cout << "Sum: " << sum(v) << "\n";
    std::cout << "Average: " << average(v) << "\n";

    if (all_positive(v))
        std::cout << "All numbers you entered were positive.\n";
    else
        std::cout << "You entered at least one negative number or zero.\n";

    // We don't have to write our own sort function: the standard provides one
    // for us.
    std::sort(v.begin(), v.end());

    // The sort is in-place, though, so we lost the original order of v.

    // Let's add a function that lets us display a range.
    std::cout << "Your input, sorted: ";
    display_range(v.begin(), v.end());
    std::cout << "\n";

    // std::sort also takes a custom comparison function.  Let's see how our
    // input looks sorted that way:
    std::sort(v.begin(), v.end(), custom_comparison);

    std::cout << "Your input, sorted using a custom comparison function: ";
    display_range(v.begin(), v.end());
    std::cout << "\n";
}
