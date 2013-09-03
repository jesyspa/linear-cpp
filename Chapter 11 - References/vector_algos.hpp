#ifndef CHAPTER_09_VECTOR_ALGOS_HPP
#define CHAPTER_09_VECTOR_ALGOS_HPP

#include <vector>
#include <iostream>

// All we have to do here is replace std::vector<int> with std::vector<int>
// const& in the parameter lists.

// Now that we can pass references, we can tell read_int_vector where to read
// the data from.  Instead of always reading from std::cin, let's make std::cin
// the default and allow the caller to pass an alternative if they want.
//
// The type of std::cin is std::istream.  We want a reference to that; we'll be
// extracting things from the stream, so it can't be a reference to const.  That
// means the type should be std::istream&.  In order to give it a default value
// we say type param_name = default_value.
std::vector<int> read_int_vector(std::istream& stream = std::cin);
int sum(std::vector<int> const& v);

// Note that we don't change the return value to std::vector<int> const&.  Why
// not?  Do not continue to the next chapter until you are comfortable with the
// answer; this is fundamental understanding that cannot be skipped over.
std::vector<int> filter_greater_than(std::vector<int> const& v, int x);

inline int average(std::vector<int> const& v) {
    if (v.empty())
        return 0;
    return sum(v)/v.size();
}

#endif
