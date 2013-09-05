/* Now that we know how to print things, it would be nice to be able to accept
 * input from the user.  However, at the moment, we don't have anywhere to put
 * such input.  Before we can start writing interactive programs, we need to
 * look at how to define variables, and for that we need to know a little about
 * types.
 *
 * The type of a variable specifies the possible values, what operations we can
 * perform on that variable, and how such operations will behave.  Let's start
 * with a few examples:
 *
 *    int is the type used for whole numbers.  We can add, subtract, multiply
 *    and divide ints, though division only gives the whole part: be careful, as
 *    this means 2/3 == 0.  There is a maximum and minimum value an int can
 *    store; if your program adds two ints that are too large, the results can
 *    be unpredictable and unpleasant.  Dividing by zero is not allowed.
 *
 *    double is the type used for numbers which aren't necessarily whole; they
 *    are sometimes also called floating point numbers.  We can add, subtract,
 *    multiply and divide doubles, but the results are not precise.  However, if
 *    you can tolerate some error, they can still be useful.  An example of a
 *    double literal is 5.3.  Dividing by zero is still not allowed.
 *
 *    bool is a type which has only two values: true and false.  It is used to
 *    represent things which can be aptly described with one of those two words.
 *    Amongst other things, comparison operators return bool.
 *
 *    char is a type for representing characters.  We haven't seen any
 *    characters by themselves yet, but the string literals we used in the last
 *    chapter were built up from them.  For example, 'a' is of type char and is
 *    the character a.  Character literals like 'a' are surrounded by single
 *    quotes, while string literals use double quotes.
 *
 *    std::string is a type used for strings; that is, fragments of text.  The
 *    types above were all primitive ones, but std::string is not, though it is
 *    standard.  In order to use an std::string, we will need to include string.
 *    It supports a large number of operations, such as getting the string
 *    length or getting the character at some index.  Note that string literals
 *    are not std::strings -- however, we can create std::strings from them.
 *
 * TODO: Add more about primitive vs nonprimitive types.
 *
 * Now that we know what types are, let's include what we need and get into main
 * to experiment a little.
 */

#include <iostream>
#include <string>

int main() {
    // When our types are as simple as those above, we can define a variable
    // just by putting the type name and then the variable name we want to use.
    int x;

    // We can now store values in x.  The stream we will be extracting out of is
    // called std::cin, and the extraction operator is >>.
    std::cout << "Enter a number: ";
    std::cin >> x;
    // Now we've extracted a number and put it in x.  We can now use this value
    // however we want; for example, let's print it back out to the user:
    std::cout << "You entered: " << x << "\n";

    /* What if the user didn't enter a number, though?  If the user doesn't
     * enter anything, the program will sit there and wait until there's some
     * input.  If the user does input something but it isn't a number, the
     * situation is worse: the program will continue, but the stream will be set
     * into a "fail" state and the value of x won't be anything meaningful.
     * We'll learn how to check for these errors very soon.
     */

    // Let's make some more variables.
    int y = x;
    std::string s;

    // Now may be a good time to talk a little about what values variables get
    // when you define them.  When we're dealing with a primitive type like int,
    // double, bool or char, the value will be garbage, and you shouldn't read
    // from it until you've given it some value.  With types like std::string,
    // we don't have to worry about that: the string will be empty.
    //
    // The way we defined y here, its initial value will be the current value of
    // x.  If we want to, we can change x and y later:
    y = 2*x;
    x = y + 5;
    // Now y will be equal to two times the value of x, and x will equal the new
    // value of y plus five.  See:
    std::cout << "x == " << x << "\n";
    std::cout << "y == " << y << "\n";

    // Let's try reading into our std::string.
    std::cout << "Enter a string: ";
    std::cin >> s;
    std::cout << "You entered: " << s << "\n";
    // If you've compiled and run this program, providing various inputs, you
    // may have noticed that only the first word you enter is read.  This is
    // because the >> for std::string works by ignoring any whitespace
    // characters, and then reading until it again sees a whitespace character.

    /* We'll look at how to read lines later; due to the way the >> operator
     * works, mixing input with it and line-by-line input can give some
     * surprising results.
     */

    return 0;
}

/* You now know enough to get input from the user, do some basic operations on
 * it, and then write it back out.  You may want to put the book aside for a
 * little and write a few of your own programs to internalize the concepts.
 * I won't repeat this notice at the bottom of every chapter, but I hope to
 * cover sufficient concepts for it to be worth it after most, anyway.
 */
