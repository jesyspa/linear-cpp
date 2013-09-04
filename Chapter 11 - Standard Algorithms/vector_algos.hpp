#ifndef CHAPTER_11_VECTOR_ALGOS
#define CHAPTER_11_VECTOR_ALGOS

#include <vector>
#include <iostream>

std::vector<int> read_int_vector(std::istream& stream = std::cin);


int sum(std::vector<int> const& v);
std::vector<int> filter_greater_than(std::vector<int> const& v, int x);

inline int average(std::vector<int> const& v) {
    if (v.empty())
        return 0;
    return sum(v)/int(v.size());
}

bool all_positive(std::vector<int> const& v);
void display_range(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end);

#endif
