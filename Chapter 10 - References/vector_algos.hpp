#ifndef CHAPTER_10_VECTOR_ALGOS_HPP
#define CHAPTER_10_VECTOR_ALGOS_HPP

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

// We're not going to change the type of sort.  We need to perform a copy of the
// vector anyway; we may as well do that when the vector is passed in -- there
// are cases where this is faster than doing it later.
std::vector<int> sort(std::vector<int> v);

// On the other hand, now that we are taking a reference to a vector here, we
// can return an iterator.  The vector we are searching is the one that is in
// the function calling us, so the iterator can still be valid after we return
// it.
//
// Instead of returning an std::vector<int>::iterator, we return an
// std::vector<int>::const_iterator.  This is also an iterator, but it doesn't
// allow us to modify the values it refers to.
std::vector<int>::const_iterator binary_search(std::vector<int> const& v, int val);

#endif
