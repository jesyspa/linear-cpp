/* As we said in main.cpp, everything in this file will be copy-pasted into all
 * files that include it.  In this project, this means main.cpp and
 * vector_algos.cpp.
 *
 * Remember how we weren't allowed to define things twice?  This is going to
 * change a little now that we are using multiple files.  We are still only ever
 * allowed to define things once per file, but there are things which we may
 * define in multiple files, as long as we define all of them the same way.
 *
 * Functions usually aren't one of these things, but we can make an exception
 * for a specific function by marking it inline.  We'll do that here with
 * average as an example.  There are a lot of trade-offs to consider when
 * choosing to do this; I won't go into the details here, but you may want to
 * consult further sources when doing this in a real project.
 *
 * Even with inline, we still have a problem.  Recall that if a file is included
 * twice, its contents will appear twice.  A definition might then be present
 * in a translation unit twice, which is not allowed.  To avoid these problems
 * we use the preprocessor.  It allows us to define macros:
 *
 *      #define MACRO_NAME arbitrary text
 *
 * When MACRO_NAME (which is traditionally written in uppercase) is encountered,
 * the arbitrary text is inserted where it was.  This can be a powerful tool,
 * but often of the "blow up in your face" variety.  We won't use the text
 * portion for now; instead, we'll use the ifndef directive, which stands for
 * "if not defined":
 *
 *      #ifndef MACRO_NAME
 *      code...
 *      #endif
 *
 * The preprocessor knows what macros are defined.  If MACRO_NAME is not defined in
 * the example above, the code is left as-is.  If it is defined, however, the
 * whole block is erased and all that ends up in the preprocessed translation
 * unit are empty lines, if that.  We will surround all our code with an ifndef,
 * and then define the macro it checks for inside it; that way, the code will be
 * kept the first time, but erased the second, preventing duplicate definitions.
 */

// Check whether we've already included this file...
#ifndef CHAPTER_08_VECTOR_ALGOS_HPP
// Mark that we've included it...
#define CHAPTER_08_VECTOR_ALGOS_HPP

/* By the way...  Modern compilers have noticed that these kind of guards are
 * used by everyone and their preprocessor supports #pragma once, which does
 * something much like the above.  This saves some pain; for example, imagine if
 * two files used CHAPTER_08_VECTOR_ALGOS_HPP to guard themselves?
 *
 * This isn't a standard feature yet, so before using #pragma once, make sure
 * you'll only be using compilers that do support it.
 *
 * Also, some people will use names like __CHAPTER_08_VECTOR_ALGOS_HPP__.  While
 * they will often work, any names with two consecutive underscores (or starting
 * with an underscore followed by a capital letter) are reserved.  If you use
 * them, it's your own fault if your program breaks.
 */

#include <vector>

// Now let's put our declarations.  Note that I changed the comments a little;
// they were more explicit than they had to be; the types are already mentioned
// in the signature, so we don't have to repeat them in the description.

// Very persistently get a vector from std::cin.
std::vector<int> read_int_vector();
// Calculate sum of all vector element values.
int sum(std::vector<int> v);
// Copy the vector, leaving only elements greater than x.
std::vector<int> filter_greater_than(std::vector<int> v, int x);

// inline is not part of the return type, it says something specifically about
// the function average.
inline int average(std::vector<int> v) {
    if (v.empty())
        return 0;
    int size = v.size();
    return sum(v)/size;
}

// We only want to "guard" the portion above.
#endif
// Take a look at vector_algos.cpp now.
