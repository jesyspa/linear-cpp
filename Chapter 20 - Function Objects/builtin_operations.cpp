#include "builtin_operations.hpp"
#include <algorithm>
#include <functional>
#include <stdexcept>

/* We can implement the built-in functions in "normal" C++; we don't have to
 * think about the language we're implementing for this purpose.  We'll just 
 *
 */

int builtin_add(std::vector<int> const& args) {
    return std::accumulate(std::begin(args), std::end(args), 0);
}

int builtin_subtract(std::vector<int> const& args) {
    if (args.size() == 1)
        return -args[0];
    if (args.size() == 2)
        return args[0] - args[1];
    throw std::runtime_error{"incorrect number of args to builtin_subtract"};
}

int builtin_multiply(std::vector<int> const& args) {
    return std::accumulate(std::begin(args), std::end(args), 1, std::multiplies<int>{});
}

int builtin_divide(std::vector<int> const& args) {
    if (args.size() != 2)
        throw std::runtime_error{"incorrect number of args to builtin_divide"};
    if (args[1] == 0)
        throw std::runtime_error{"division by zero"};
    return args[0] / args[1];
}

