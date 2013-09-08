/* Welcome back.  In the following few chapters we'll look at how variables work
 * in C++, and how we can perform input and output.
 *
 * In this example, we'll meet the preprocessor and look at some very basic
 * output.
 */

// This, like any line starting with a #, is a preprocessor directive.  Such
// lines are instructions for manipulating the program text.  The #include
// directive, which is what we will use most often, states that the contents of
// a certain file should be inserted where the directive is.  In this case, we
// ask for the file iostream.  The io stands for input output, and that's what
// we'll be using it for.
#include <iostream>

/* Now that we have the things we need to do input and output available to us,
 * we can declare and define the main function.  Let's take a look at those two
 * terms first, though:
 *
 * A declaration introduces a name into the program, and specifies the type of
 * what that name refers to.  In the last program, we declared main as an int(),
 * which you can read as "a function taking no parameters and returning int".
 * We can declare a name as many times as we want, as long as we declare it to
 * be the same type every time.  Using a name before it has been declared is
 * usually not allowed; I'll mention exceptions as we come to them.
 *
 * When talking about functions, a definition does everything a declaration does
 * but also provides the body of the function.  In the example in the foreword,
 * we define main: if we didn't, we'd get an error when trying to compile the
 * program.  Every definition is automatically also a declaration.  However,
 * unlike with declarations, it is generally not allowed to define something
 * multiple times.  The rules become more nuanced when we start writing programs
 * that span multiple files, but you can safely assume it will not work for now.
 *
 * With these terms explained, we can now properly state why we wanted to
 * include iostream before doing anything else: we want to refer to names
 * declared in there.
 */

// Now we define (and thus also declare) the main function:
int main() {
    /* Output in C++ is stream-based.  We have a stream, and some value we want
     * to put into it, and then we use the << operator to insert the value into
     * the stream.
     */

    // More concretely, this will insert the string literal "Hello world!\n"
    // into the stream std::cout.
    //
    // A string literal represents the text contained in it, except that some
    // character sequences (such as \n) are converted into characters you can't
    // easily write; for example, \n ends the line and goes to the next one.
    //
    // std::cout is the output stream we will use most.  Anything piped into it
    // simply gets printed by the program.  You can see std::cout as a single
    // name for now.
    //
    // Putting all the above together, this will print Hello World! and then
    // end the line, so anything we print later will end up on the next line.
    std::cout << "Hello world!\n";

    // String literals aren't the only the only things we can print.  You can
    // print numbers, too, in exactly the same way.
    //
    // Note that this only prints 5 -- if we want to print a newline, we need to
    // do that separately.
    std::cout << 5;

    // We often want to print multiple things, and repeating std::cout over and
    // over again would get tedious.  Fortunately, we can chain insertions:
    ((((std::cout << " == ") << 3) << " + ") << 2) << "\n";

    // TODO: Explain about std::cout << " == " being an expression.
    // This works because the result of std::cout << " == " is again std::cout.
    // The above is equivalent to writing five statements where std::cout is
    // named every time.  Even better, though, the way the << operator is
    // defined lets us skip all the parentheses and write things like:
    std::cout << 3 << " plus " << 2 << " equals " << 5 << "\n";

    // This last form is what we will use most.

    return 0;
}

/* The explanation that std::cout should be treated as a single name may be
 * unsatisfying to those with more programming experience.  If you really wish
 * to see it as a compound entity, you can read it as "the thing named cout from
 * std".  There's a variety of reasons we'd like to be able to have different
 * places provide things with the same name, and we'll eventually cover them.
 * However, giving that whole explanation now would be entirely unlinear, and
 * wouldn't help with understanding the coming few chapters.
 *
 * Here's what the practical part boils down: several names separated by :: are
 * a compound name for something, and we currently don't need to distinguish
 * compound names from non-compound ones.  We will see many such names, for
 * types, functions, and variables, and they shouldn't come as a surprise.  When
 * talking about things we will sometimes drop the std::, but we'll always write
 * it out in code until we get far enough for the proper rules to be introduced.
 */
