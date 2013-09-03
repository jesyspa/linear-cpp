/* Now we're getting to the interesting stuff!  We'll leave read_int_vector
 * as-is; go ahead and look below it for the cool new stuff.
 */
#include "vector_algos.hpp"
#include <iostream>
#include <string>
// This is a header we've not seen before; it allows us to use some features of
// vectors.  I'll introduce what exactly it brings in when we get to it.
#include <iterator>

// One thing I'll say already, though, is that we will be using a type called
// std::vector<int>::iterator a lot.  It will be introduced very soon; for now I
// want to save us some typing and give it a shorter name.
using iterator = std::vector<int>::iterator;
// The above makes iterator another name for std::vector<int>::iterator.

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

std::vector<int> sort(std::vector<int> v) {
    /* The sorting algorithm we'll be implementing is called quicksort.  It
     * works as follows:
     *
     *  - Take a vector.  If it is empty or has one element, we are done.
     *  - Otherwise, choose an element x from it.
     *  - Rearrange the vector so that all elements less than x are to the left
     *    of x, and all elements greater than or equal to are to the right.
     *  - Quicksort all the elements to the left of x, then all elements to the
     *    right of x.
     *
     * This may feel like cheating: we're making use of quicksort while we're
     * defining what it is!  Never the less, we'll be able to write the code
     * exactly like this and it'll work.  That's because every time we use
     * quicksort we use it on a smaller vector than before: eventually, we'll
     * get to vectors that are empty or have one element, and there we don't
     * call quicksort any more.  This pattern of a function calling itself is
     * called recursion.
     *
     * We could go and write this using just the things we know already, but the
     * number of copies that we'd need to make would be overwhelming.  Every
     * time we want to wanted to sort a part of the vector we'd have to copy
     * that part into a separate vector, sort it (more copies!), and then copy
     * it back.  Wouldn't it be nice if there was some way to indicate a
     * "subvector"?
     *
     * As usual, it turns out there is.  The solution is to pass not a vector
     * but an iterator range.  An iterator is a general concept, but we'll be
     * specifically working with std::vector<int>::iterators today.  It's a
     * random access iterator, which gives us the most freedom when using it.
     * We'll look at other kinds of iterators later; some of what I say here
     * might not apply to them.
     *
     * Getting an iterator is easy: v.begin() and v.end() both give us
     * iterators.  v.begin() is the iterator corresponding to the first element
     * of v.  v.end() is the iterator corresponding to one past the last
     * element.  That means that v.end() does not have an associated element!
     * It turns out that having this "imaginary element" makes many things
     * easier.  For example, if the vector is empty, v.begin() will also refer
     * to the imaginary element, and we know that v is empty if and only if
     * v.begin() == v.end().
     *
     * But, let's say we have an iterator:
     *
     *      auto it = v.begin(); // auto becomes std::vector<int>::iterator
     *
     * What can we do?  As we showed with v.end() above, we can compare
     * iterators.  We can also add a value to an iterator:
     *
     *      it += 2; // now v.begin() refers to the third element.
     *
     * Usually we want to go one element at a time, and so we use ++it.
     *
     * Finally, we can get what element an iterator refers to by dereferencing
     * it:
     *
     *      int i = *it; // same as int i = v[2]; here.
     *
     * Note that this is only allowed if it refers to an element -- *v.end() is
     * not allowed.  (More precisely, it isn't defined: the result is
     * unpredictable and likely unpleasant.)
     *
     * Now that we know the basic operations iterators support, we can write
     * our sorting function!
     */

    // We'll start by defining two helper functions.  One does the rearranging
    // step, and we'll call it partition.  It takes the range it should
    // rearrange, uses the first element of that range to perform the
    // rearranging (we call that element the pivot), and then returns an
    // iterator to where the pivot ended up.
    //
    // The other function will perform the result of the algorithm.  It doesn't
    // need to return anything, but it takes the range to be sorted.  Our sort
    // function delegates most of its work to it; I find that this makes the
    // name sort_impl a good choice, as it is the "real implemenation" of the
    // sort function.
    //
    // Recall that we made iterator another name for std::vector<int>::iterator.
    // Now's the time to make use of that and save us some typing!
    iterator partition(iterator begin, iterator end);
    void sort_impl(iterator begin, iterator end);

    // As v is already a copy, we can sort it in-place and then return it.
    sort_impl(v.begin(), v.end());
    return v;
}

void sort_impl(iterator begin, iterator end) {
    // Redeclaration; our previous one was only in the scope of sort.
    iterator partition(iterator begin, iterator end);

    // Here comes the real work!  First of all, we want to know whether the
    // range [begin,end) contains more than one element.  Just like we can add a
    // number to an iterator, we can subtract two iterators to get the number of
    // elements in the range they create.  If we have one or less, we'd like to
    // return.
    if (end - begin <= 1) {
        // sort_impl returns void, so what value do we give when returning from
        // it?  No value is fine.  (Don't try this in a non-void function.)
        return;
    }

    // Let's partition the thing and see what the two subranges we get are.
    auto pivot = partition(begin, end);
    // The first subrange is [begin,pivot).  Note that pivot acts as the end
    // iterator here, so even though though there is an element at that
    // position, we can assume our algorithms won't do anything with it.
    //
    // We know that pivot is already in the correct position (how?).  We also
    // know that pivot != end, so we can increment pivot.  We thus use pivot+1
    // as the beginning of our second range, and this will be correct.
    sort_impl(begin, pivot);
    sort_impl(pivot+1, end);
}

iterator partition(iterator begin, iterator end) {
    // Now for the partitioning.  We'll want to iterate over the range and keep
    // track of where the pivot is.  We know the range isn't empty, so we can
    // increment begin.  Notice how we're using postincrement; this means the
    // value of begin is changed, but pivot still gets the old value.
    //
    // We need to put this outside the for loop because we want to use it later.
    auto pivot = begin++;

    for (; begin != end; ++begin) {
        if (*pivot > *begin) {
            // We use a handy function called std::swap.  It swaps the values of
            // two variables.  Here, swapping *pivot and *begin means swapping
            // the values of two vector elements.
            //
            // If we find an element that should go before the pivot, we swap it
            // with the pivot.  We then move the pivot iterator one further, and
            // swap the now-pivot with that.
            //
            // For example, let 3 be the pivot:
            //
            //      1, 3, 5, 7, 6, 2, 4, 8,
            //         ^           ^        ^
            //   pivot |     begin |    end |
            //
            // We swap *pivot and *begin:
            //
            //      1, 2, 5, 7, 6, 3, 4, 8,
            //         ^           ^        ^
            //   pivot |     begin |    end |
            //
            // We increment the pivot iterator
            //
            //      1, 2, 5, 7, 6, 3, 4, 8,
            //            ^        ^        ^
            //      pivot |  begin |    end |
            //
            // And then we swap *pivot and *begin again:
            //
            //      1, 2, 3, 7, 6, 5, 4, 8,
            //            ^        ^        ^
            //      pivot |  begin |    end |
            //
            // Now pivot again refers to 3, all elements to the left of it are
            // less than 3, and all elements between it and begin are greater
            // than 3.
            std::swap(*pivot, *begin);
            ++pivot;
            std::swap(*pivot, *begin);
        }
    }

    // At the end, pivot refers to where our pivot is, so we can just return it.
    return pivot;
}

// Phew!  Now we've gotten sorting working, let's implement searching.  The
// algorithm is based on a similar principle.  We know that the vector is
// sorted, so if we encounter an element greater than the element we're looking
// for, we can assume it isn't in any of the above.  We can put a similar lower
// bound, and by always looking at the number in the middle of the bound we'll
// be able to narrow down our search very quickly.

bool binary_search(std::vector<int> v, int val) {
    // We name our bounds bottom and top.
    auto bottom = v.begin(), top = v.end();
    while (top != bottom) {
        // Find an element half-way in the range.
        auto mid = bottom + (top - bottom)/2;
        // The way we choose subranges here is similar to how we choose them
        // with quicksort.  If our range is bounded by mid from above, mid as
        // end works fine.  If from below, we want to exclude mid from it.
        if (*mid < val)
            bottom = mid+1;
        else if (*mid > val)
            top = mid;
        else
            return true;
    }
    // If bottom == top, the range of possible elements is empty and so we
    // haven't found it.
    return false;
}

/* At the moment, our binary search only checks whether the value is in the
 * vector.  It doesn't specify where in the vector it is; had we wanted to do
 * that, we'd have to come up with some value to use for an invalid index.  We
 * could use the size of the vector, or -1, or some other value that cannot
 * otherwise be attained, but that's hardly a neat solution.
 *
 * What if we returned an iterator?  v.end() would be the idiomatic value to
 * return, and the changes to the code would be minor.  It would, however, be
 * a grave error in this case.  When we call binary_search we pass it a vector.
 * That vector is copied and is called v inside binary_search.  When we return
 * from binary_search, v will be destroyed, and any iterators still refering to
 * its elements will become unusable: if we returned one to the caller, it
 * wouldn't be able to do anything with it.
 *
 * Speaking of nasty things: don't compare iterators from different vectors.
 * The result you get won't be meaningful.
 *
 * We can run into a similar bug with function return values.  For example:
 *
 *      auto it = filter_greater_than(v, 5).begin();
 *
 * If v is an std::vector<int> this will compile.  However, the vector returned
 * by filter_greater_than is a temporary.  Temporaries exist until the outermost
 * expression they are part of has been evaluated fully.  In this case, that's
 * the expression filter_greater_than(v, 5).begin().  That means that by the
 * next statement, the temporary has been destroyed and the value in it is
 * unusable.
 *
 * Knowing how long things live for is a critical part of writing correct C++
 * programs.  We didn't have to worry about it until now, due to there being no
 * way to refer to an object that has been destroyed; now that iterators are in
 * the picture, extra care must be taken.
 */

/* Now that you know iterators, try rewriting the program we've written earlier
 * to use them.  In the next chapter we'll take a look at how to save ourselves
 * some copying with references.
 */
