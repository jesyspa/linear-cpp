/* So far, we've done all looping with while.  However, if you wrote some of
 * your own code after reading the last chapter, you probably noticed that a lot
 * of it looked like
 *
 *      std::size_t i = 0;
 *      while (i < v.size()) {
 *          statements...
 *          i += 1;
 *      }
 *
 * In fact, code like this is so common that there's a special syntactic
 * construct when we want to do something "for every X".  Rephrased to use it,
 * the above becomes
 *
 *          // Initialisation ;  Condition  ; Step
 *      for (std::size_t i = 0; i < v.size(); i += 1) {
 *          statements...
 *      }
 *
 * The initialisation is a definition or expression.  You can define multiple
 * variables of the same type, but you cannot define multiple variables of
 * different types -- there's simply no room.  The next part is the condition,
 * which is exactly like in a while loop.  The last is the step; it behaves much
 * as if it were the last statement in the body of the for, but is limited to
 * being an expression.
 *
 * Any of the three parts may be omitted.  If you omit the initialisation or
 * step, that part will do nothing; if you omit the condition, it will always
 * evaluate to true.  You will sometimes see for (;;) being used instead of
 * while (true) -- the two are equivalent.
 *
 * A little note about how variables behave: when we define a variable in a
 * block of code, it will not be visible outside that block.  We will have a
 * much more rigorous explanation of this in the next chapter; for now it
 * suffices to say that if you define a variable in an if, while, or for loop,
 * including in the initialisation of the for loop, you will not be able to use
 * it outside that conditional or loop.
 *
 * Let's rewrite yesterday's program to use a for loop.
 */

#include <iostream>
#include <vector>

int main() {
    int x;
    std::vector<int> v;

    std::cout << "Enter as many numbers as you want:\n";
    while (std::cin >> x)
        v.push_back(x);

    if (v.empty()) {
        std::cout << "An empty sequence has no greatest or least element.\n";
        return 0;
    }

    // We want greatest_index and least_index to be visible outside the loop, so
    // we keep them here.
    std::size_t greatest_index = 0;
    std::size_t least_index = 0;

    // i += 1 is such a common operation that there's a shortcut: ++i does
    // exactly the same thing, while --i is i -= 1.  There's also i++, which
    // increments i, but evaluates to the old value.  If you can use either one
    // prefer ++i; it's a good habit to get into for when we're dealing with
    // more complex types than just integers.
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (v[i] > v[greatest_index])
            greatest_index = i;
        if (v[i] < v[least_index])
            least_index = i;
    }

    std::cout << "Greatest element " << v[greatest_index] << " is at index " << greatest_index << ".\n";
    std::cout << "Least element " << v[least_index] << " is at index " << least_index << ".\n";

    /* It turned out that what we did with the vector is so common that even the
     * for syntax wasn't quite enough.  C++11 adds range-based for loops, which
     * allow us to not have to deal with indices.  Instead, we can write
     *
     *      for (int e : v) {
     *          statements...
     *      }
     *
     * This will run statements once for every element of v, and during that run
     * e will be set to that element.  We can't easily get at the index any
     * more, but we usually don't need it; for example, if we just want to take
     * the sum, we only care about the elements and not about where in the
     * vector they are.
     *
     * At the moment, we also can't modify the elements while looping over the
     * vector this way; however, we'll see a way to do that fairly soon.
     */

    int total = 0;
    for (int e : v)
        total += e;

    std::cout << "Sum: " << total << "\n";
    std::cout << "Integer average: " << total/v.size() << "\n";

    /* If we changed the type of v from vector<int> to vector<double>, much of
     * the program would work.  However, we'd have to change both int total and
     * int e above.  When our programs get bigger, changing things like this
     * will be rather a pain.  For that reason, we can use auto in order to have
     * the compiler figure out the correct type for us.  This isn't a magic word
     * that will solve all your problems, but it can help significantly.
     */

    // For example, let's output all the elements of v:
    for (auto e : v)
        std::cout << "v contains: " << e << '\n';

    // Try changing the types in this program and see what works and what
    // breaks.

    return 0;
}
