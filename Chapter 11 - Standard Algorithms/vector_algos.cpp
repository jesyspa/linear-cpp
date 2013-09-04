#include "vector_algos.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>

std::vector<int> read_int_vector(std::istream& stream) {
    std::vector<int> result;

    while (true) {
        // Instead of using a loop here, we can use std::copy.
        //
        // This may be a little surprising: after all, std::istream doesn't look
        // like a collection, how could it have begin and end iterators?  What
        // would it mean to add a number to the iterator; would we be skipping
        // some inputs?  Would subtracting a number mean we go back to earlier
        // inputs?
        //
        // The answer is that unlike vector iterators, std::istream iterators aren't
        // random access.  You can still do a few of the things we could do with
        // vector iterators, but nowhere near as many.  In fact, std::istream
        // iterators are input iterators: that's the most limited family of
        // iterators available.  You can only increment them, read from them,
        // and compare them for equality.  For copying, we don't need any more.
        //
        // We will be using the type std::istream_iterator<int>.  If we want to
        // create a temporary object of a type, we can use the type followed by
        // a pair of curly braces.  Within these curly braces we can give
        // arguments for how the temporary should be constructed.  For example,
        // std::vector<int>{1, 2, 3} would create a vector containing the ints
        // 1, 2, and 3.  We can do a similar thing for std::istream iterators,
        // where we pass a stream, and get the current iterator for that stream.
        // If we don't pass anything, we get an end iterator that works for any
        // stream.
        //
        // Thus, our begin iterator is std::istream_iterator<int>{stream}, while
        // our end iterator is std::istream_iterator<int>{}.
        //
        // Where do we copy to?  We can't copy to result.begin(), because there
        // won't be enough room there.  Instead, the standard library provides
        // us with std::back_insert_iterator<std::vector<int>>.  That's a
        // mouthful, but we can make one with std::back_inserter(result).
        //
        // All in all, we get:
        std::copy(std::istream_iterator<int>{stream}, std::istream_iterator<int>{},
                std::back_inserter(result));

        // This may seem like a mouthful, but it's a good idea to understand it;
        // iterators provide a powerful abstraction over much more than simple,
        // linear containers like vector.

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
    // We use std::accumulate.  It takes a range and an initial value, and then
    // uses the + operator to add all the values together.  There's another
    // version which also takes a function to use instead of the + operator, but
    // we don't need that here.
    //
    // begin, end, and initial value 0.  Tada!  And don't worry - chances are
    // that this is as efficient as writing out the loop.
    return std::accumulate(v.begin(), v.end(), 0);
}

std::vector<int> filter_greater_than(std::vector<int> const& v, int x) {
    // While there is an std::copy_if that we could use to implement this
    // function, we currently don't have the tools to turn x into a function
    // that returns true for values greater than x, and false for all other
    // values.  We'll see how to do it soon enough, though!
    std::vector<int> result;
    for (auto e : v)
        if (e > x)
            result.push_back(e);
    return result;
}

bool is_positive(int x) {
    return x > 0;
}

bool all_positive(std::vector<int> const& v) {
    // This is a very straightforward use of std::all_of.  It takes a range and
    // a predicate -- a function taking some values and returning bool -- and
    // then returns true if the predicate returns true for all values in the
    // range.  If the range is empty, it also returns true; this is a nicer
    // generalisation than if the empty range resulted in false.  (For instance,
    // it means that every subrange of a range that returns true will also
    // return true.)
    return std::all_of(v.begin(), v.end(), is_positive);
}

void display_range(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end) {
    // Let's surround the output with nice curly braces.
    std::cout << "{ ";

    // The way to print things with iterators is much the same to how one reads
    // things with them.  We use an std::ostream_iterator<int>, which we give a
    // stream to write to and a bit of text to print after each value.
    //
    // std::ostream_iterators are output iterators.  They support all the
    // operations of input iterators, except that you cannot read from them; you
    // can, however, write to them, and whatever you write will be printed.  You
    // should increment them between each write.
    std::copy(begin, end, std::ostream_iterator<int>{std::cout, " "});

    std::cout << "}";

    /* By the way, have you noticed that even though copy works on two ranges,
     * we only need to pass the end iterator of the one we're copying from?
     * That's because the standard library assumes that the other will be long
     * enough.  If that's not the case, unpredictable and almost certainly
     * unpleasant things will happen.  (Unpredictable and unpleasant things
     * happening is a common thing in C++ if you're not careful; there'll be a
     * chapter on it later.)
     */
}

/* Notice how we're mentioning the fact that we're operating on vectors of ints
 * everywhere.  However, if we wanted to write these algorithms for a vector of
 * doubles, the code would likely be much the same.  In the next chapter we'll
 * take a look at how we can make these functions work on a vector of any type
 * that supports the right operations.  Our sum function will even be able to
 * take the sum of a vector of strings!
 */
