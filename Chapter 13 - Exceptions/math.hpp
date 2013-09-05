#ifndef CHAPTER_13_MATH_HPP
#define CHAPTER_13_MATH_HPP

#include <utility>

// The equation will likely have two roots, so we return an std::pair.  This is
// just a type that lets us store two values; if we have a pair p then the first
// value can be accessed as p.first, and the second as p.second.  Nothing
// spectacular, but it means we can return two values.
std::pair<double, double> find_roots(double a, double b, double c);

#endif

