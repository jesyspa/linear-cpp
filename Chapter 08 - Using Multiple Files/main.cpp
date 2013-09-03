/* Suggested reading order: main.cpp, vector_algos.hpp, vector_algos.cpp
 *
 * This chapter is unlike all the previous ones, because instead of having a
 * single main.cpp file the directory should contain main.cpp, vector_algos.hpp
 * and vector_algos.cpp.  We're going to leave the previous program almost
 * unchanged, but instead of lumping everything together into one file we'll
 * neatly split it out.  You can see our main function below: it is entirely
 * unchanged.
 *
 * The new files added are another source file and a header file.  The source
 * file, vector_algos.cpp, behaves just like main.cpp; it will be compiled the same way, as
 * described further.  We are going to define all our algorithms for working on
 * vectors in there.
 *
 * The header file, vector_algos.hpp, is somewhat different.  We will not give
 * it to the compiler directly; instead, we will include it in our source files.
 * This is only marginally useful in this example, as only main.cpp really needs
 * to include it.  However, as our projects grow large we won't want to
 * duplicate all our function declarations by hand.  Instead, we will write them
 * in header files and use include directives to copy their contents into our
 * source files.
 *
 * This is exactly what the include directive does: it takes everything in that
 * file and literally copy-pastes it where our include directive was.  Do not
 * expect any kind of special treatment: if you include a file twice, it will be
 * pasted in twice.  If file A includes file B, and file B includes file C, file
 * A will get a copy of file C inside it.  If file A includes file B, and file B
 * includes file A, your program will not compile.
 *
 * What happens when a program is compiled, anyway?  The process can be split
 * into three stages:
 *
 *  - First of all, the preprocessor is run over all the files.  This removes
 *  comments and handles all preprocessor directives.  After this, every source
 *  file has become a single compilable entity called a Translation Unit.
 *  Header files are no longer necessary.
 *  - Secondly, the compiler runs on each source file and outputs an object
 *  file.  This is the compiled code for that one file; it is not yet an
 *  executable, as not all functions are necessarily defined.  It is here that
 *  most of the translation is done; after this step, finding the C++ code back
 *  is not possible.
 *  - Thirdly, the linker takes all our object files and then links them into an
 *  executable, which we can run.
 *
 * Why not glue all the source files together before compiling?  C++ is a
 * complex language, and compiling it takes a long time.  By doing the
 * preprocessing and compiling separately for every file, we don't need to
 * recompile translation units that haven't changed since we last compiled.
 * Only linking needs to look at all of the files, but that is relatively fast.
 * Even for small projects, this can make the difference between being able to
 * test your changes directly and having to wait a minute or two for it to
 * build.
 *
 * Because of this, it is a good idea to minimize the number of things you
 * include: the more headers a file depends on, the more likely it is it will
 * need to be recompiled.  The advice boils down to "include everything you
 * need, and no more", which admittedly is not all that specific.
 *
 * You might have noticed that so far, we've not seen the preprocessed files or
 * object files.  This is because with a project this small, we can ask the
 * compiler to keep the results in memory between the steps.  Even with bigger
 * projects, the preprocessing output is usually not stored; object files,
 * however, are usually written to disk for reusability.
 *
 * Enough chatter, let's look at the program.
 */

// What to include and in what order is an interesting question.  Due to the
// copy-paste nature of includes, if vector_algos.hpp includes iostream and
// vector, we don't need to include those two.  Can we be sure it will, though?
// We know that the only work we do on vectors is with the functions from it, so
// that's fine.  We don't have any reason to be sure it will include iostream,
// though, so we include that ourselves.
//
// As to the order, you should do your best to stop includees relying on the
// prior includes of their includers.  A mouthful?  Let's say A includes B and
// then C.  If C needs B, C should include B itself, not rely on A including B
// first.  Thus, include your own headers first of all, then the headers of the
// third-party libraries you use, and finally the standard library headers.
#include "vector_algos.hpp"
#include <iostream>


// Look at how clean and simple this is!
// Once you're done admiring it, read vector_algos.hpp
int main() {
    auto v = read_int_vector();

    std::cout << "Average: " << average(v) << "\n";
    std::cout << "Sum: " << sum(v) << "\n";

    std::cout << "Elements greater than 5:";
    for (auto e : filter_greater_than(v, 5))
        std::cout << " " << e;
    std::cout << "\n";

    // By the way, we've been writing return 0; at the end of every main
    // function.  As I said before, the main function is weird: for example, you
    // can't call it from inside your program.  Another (nice) quirk it has is
    // that you are allowed to omit the return statement at the end, and the
    // compiler will assume you returned 0.  This means we can stop writing it
    // out now and let the compiler do the work.
    //
    // As you may have noticed, I'm extremely lazy and love letting software do
    // work for me.
}
