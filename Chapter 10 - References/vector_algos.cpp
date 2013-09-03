#include "vector_algos.hpp"
#include <iostream>
#include <string>

// Note that we shouldn't repeat the default value here; we already know it from
// the header!
//
// Seeing as we can't rely on the user being present any more, let's drop most
// of the output statements.  The ones we keep shouldn't go to std::cout any
// more; C++ provides a stream std::cerr that we can use the same way we used
// std::cout, but that is intended for errors.  We'll use that for reporting
// what characters we ignored.
std::vector<int> read_int_vector(std::istream& stream) {
    std::vector<int> result;
    int x;

    while (true) {
        while (stream >> x)
            result.push_back(x);

        if (stream.eof())
            break;

        stream.clear();

        std::string s;
        std::getline(stream, s);

        std::cerr << "Warning, ignoring: " << s << "\n";
    }

    return result;
}

int sum(std::vector<int> const& v) {
    int total = 0;
    for (auto e : v)
        total += e;
    return total;
}

std::vector<int> filter_greater_than(std::vector<int> const& v, int x) {
    std::vector<int> result;
    for (auto e : v)
        if (e > x)
            result.push_back(e);
    return result;
}

// We move the declarations out now that they're no longer a surprise.
using iterator = std::vector<int>::iterator;
iterator partition(iterator begin, iterator end);
void sort_impl(iterator begin, iterator end);

std::vector<int> sort(std::vector<int> v) {

    sort_impl(v.begin(), v.end());
    return v;
}

void sort_impl(iterator begin, iterator end) {
    if (end - begin <= 1)
        return;

    auto pivot = partition(begin, end);
    sort_impl(begin, pivot);
    sort_impl(pivot+1, end);
}

iterator partition(iterator begin, iterator end) {
    auto pivot = begin++;

    for (; begin != end; ++begin) {
        if (*pivot > *begin) {
            std::swap(*pivot, *begin);
            ++pivot;
            std::swap(*pivot, *begin);
        }
    }

    return pivot;
}

std::vector<int>::const_iterator binary_search(std::vector<int> const& v, int val) {
    auto bottom = v.begin(), top = v.end();

    while (top != bottom) {
        auto mid = bottom + (top - bottom)/2;
        if (*mid < val)
            bottom = mid+1;
        else if (*mid > val)
            top = mid;
        else
            return mid;
    }

    return v.end();
}


