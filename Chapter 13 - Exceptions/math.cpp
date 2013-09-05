#include "math.hpp"
#include <cmath>
#include <stdexcept>

// This is a straightforward implementation of the quadratic formula:
// http://en.wikipedia.org/wiki/Quadratic_formula
std::pair<double, double> find_roots(double a, double b, double c) {
    // Nobody forces us to use const when dealing with locals, but it is a
    // sensible thing to do if you know the value will not change.
    auto const determinant = b*b - 4*a*c;

    // Instead of throwing std::runtime_error, we throw std::domain_error.  This
    // is a very similar type, varying mostly in name.  It is intended to be
    // used when "a mathematical function is not defined for the value of the
    // argument", which is what we have here.
    if (determinant < 0)
        throw std::domain_error{"no real roots."};

    // std::sqrt returns the square root of its argument.
    // We make these to save ourselves from computing some values twice.
    auto const two_a = 2*a;
    auto const d_part = std::sqrt(determinant);

    // std::make_pair makes a pair.  Duh.
    return std::make_pair((-b+d_part)/two_a, (-b-d_part)/two_a);
}

/* We've now written all our throwers.  They throw std::runtime_error and
 * std::domain_error, so we'll want to catch those two in main.  Let's go there
 * and make that work.
 */
