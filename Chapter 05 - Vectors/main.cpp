/* We can now take as much input from the user as we want, but we can still only
 * store a limited number of numbers at any one time.  In this chapter we will
 * introduce vectors, which allow for storing an arbitrary number of values.
 * They are, in a way, similar to strings, which allow you to store as many
 * characters as you want.
 *
 * A vector can store any of the types we named before, but any particular
 * vector must store only objects of one type.  We can specify what type this is
 * when we declare the vector.  For example, if we'd like v to be a vector that
 * stores ints, we say
 *
 *      std::vector<int> v;
 *
 * Once a vector is declared to store things of a certain type, we can not
 * change it to store something else.  On the bright side, this means that given
 * a vector we always know what type of things it contains.  We also have
 *
 *      v.size() // the number of elements in the vector
 *      v.empty() // whether the vector is empty
 *      v[0] // the first element
 *      v[1] // the second element
 *      ... // etc.
 *
 * As an example, we'll write a program that reads as many numbers as the user
 * provides, and then finds the index of the greatest and least elements.
 */

#include <iostream>
// We don't use strings in this example, but we do need to include vector to use
// vectors.
#include <vector>

int main() {
    int x;
    // Just like with std::string, if we don't specify the starting value for
    // the vector it will be empty.
    std::vector<int> v;

    std::cout << "Enter as many numbers as you want:\n";
    while (std::cin >> x) {
        // push_back adds an element at the end of the vector.  This means that
        // all existing values stay where they were, and the new value has the
        // highest index.  push_front, on the other hand, puts the new element
        // at index 0 and moves the rest up; it can be useful, but is much
        // slower.
        v.push_back(x);
    }

    // The user has entered as many numbers as he wanted to.  Now we need to
    // loop over the vector to find the greatest and least elements.  For this
    // we introduce another type.  Technically, the correct type to use is
    // std::vector<int>::size_type.  However, that's rather a mouthful and we
    // will instead use std::size_t, which is the same thing on many systems.
    // For small vectors and normal platforms this'll work.
    std::size_t i = 0;
    std::size_t greatest_index = 0;
    std::size_t least_index = 0;
    while (i < v.size()) {
        if (v[i] > v[greatest_index])
            greatest_index = i;
        if (v[i] < v[least_index])
            least_index = i;
        i += 1;
    }

    // By the way, if the user entered no numbers, we don't want to print
    // v[greatest_index] or v[least_index]; that would be accessing an element
    // which doesn't exist.  C++ doesn't specify what happens if we try to do
    // that, but it may very well be unpleasant.
    //
    // Why is it okay that we're only performing this check here, and not before
    // we find the greatest and least element?
    if (v.empty()) {
        std::cout << "An empty sequence has no greatest or least element.\n";
    } else {
        std::cout << "Greatest element " << v[greatest_index] << " is at index " << greatest_index << ".\n";
        std::cout << "Least element " << v[least_index] << " is at index " << least_index << ".\n";
    }

    return 0;
}
