/* Suggested reading: main.cpp, vector_algos.hpp, vector_algos.cpp
 *
 * We're going to write some more functions now.  We'll start by implementing a
 * sorting algorithm and then implement a binary search function.  Binary search
 * lets us find a value in a vector faster, but it requires that the vector be
 * sorted.
 *
 * Let's take a look at the main function first, which gives a high-level
 * overview of what's going on:
 */

#include "vector_algos.hpp"
#include <iostream>

int main() {
    // Looking at this code, we can deduce that sort probably has type
    //      std::vector<int>(std::vector<int>)
    // and binary_search has type
    //      bool(std::vector<int>, int)
    auto v = read_int_vector();
    auto sorted_v = sort(v);

    std::cout << "You entered:";
    for (auto e : sorted_v)
        std::cout << " " << e;
    std::cout << "\n";

    for (int i = 0; i < 10; ++i) {
        if (binary_search(sorted_v, i))
            std::cout << i << " was amongst the numbers you entered.\n";
        else
            std::cout << i << " was not amongst the numbers you entered.\n";
    }
}
