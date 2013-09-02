/* This is a fairly simple file.  We copy over the functions in the last
 * chapter.  Nothing special has to be done here.
 *
 * Perhaps important to note is that while we need to declare things in main.cpp
 * (or a header it includes) for them to be visible during the compilation
 * stage, everything we define in this file will by default be visible in the
 * linker stage.  That means that functions we define can still cause double
 * definition errors.  We will later see how to fix that.
 */
#include "vector_algos.hpp"
#include <iostream>
#include <string>

std::vector<int> read_int_vector() {
    std::vector<int> result;
    int x;

    std::cout << "Enter as many numbers as you want:\n";

    while (true) {
        while (std::cin >> x)
            result.push_back(x);

        if (std::cin.eof())
            break;

        std::cin.clear();

        std::string s;
        std::getline(std::cin, s);

        std::cout << "Warning, ignoring: " << s << "\n";
    }

    std::cout << "End of file encountered, stopping input.\n";
    return result;
}

int sum(std::vector<int> v) {
    int total = 0;
    for (auto e : v)
        total += e;
    return total;
}

std::vector<int> filter_greater_than(std::vector<int> v, int x) {
    std::vector<int> result;
    for (auto e : v)
        if (e > x)
            result.push_back(e);
    return result;
}

