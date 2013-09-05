/* So far I've introduced you to a few tools that you can use to write programs
 * of your own.  You can read input, store as much of it as you want, and then
 * perform calculations using loops.
 *
 * In this chapter, we'll introduce you to your first meta-tool: a tool for
 * making tools.  While you face relatively easy problems such things may seem
 * to cost more than they saves you, but the slightest increase in complexity
 * will make them irreplacable.
 *
 * I am talking about functions.
 *
 * We've already seen the main function.  It had type int() and was where we put
 * by far most of our code.  Other functions are going to have much the same
 * structure:
 *
 *      return_type function_name() {
 *          statements...
 *      }
 *
 * This should look fairly familiar now.  The function must return a value of
 * its return type; if we wish to not return anything we can use the void type,
 * of which no value can be made.
 *
 * Before moving on to more advanced possibilities, let's look at some examples.
 */

#include <iostream>
#include <vector>
#include <string>

// We often write code which reads as many numbers as the user is willing to
// give and stores them in a vector.  Let's write a function that does that.
std::vector<int> read_int_vector() {
    std::vector<int> result;
    int x;

    std::cout << "Enter as many numbers as you want:\n";

    // We could use much the same implementation as we used in the last
    // examples, which assumes that if the input failed, there is nothing more
    // to read.  However, let's be a little more thorough and insist that the
    // user keep entering data until he closes the stream.  If a file is being
    // redirected this will happen when the end of the file is reached; when
    // entering data directly, Control-D will do the job on Linux, while
    // Control-Z will work on Windows.
    //
    // Seeing as the exit condition of this loop is rather complicated, we'll
    // make it and endless loop and break out of it differently.
    while (true) {
        // Read all the input we can.
        while (std::cin >> x)
            result.push_back(x);

        // Now we know something went wrong.  If we reached end of file, we can
        // break out of the loop.  Otherwise, we want to fix the stream and
        // continue.
        if (std::cin.eof()) {
            // The break statement does exactly what it says on the tin: it
            // breaks out of the innermost loop we happen to be in.  It has a
            // sibling: the continue statement, which skips to the end of this
            // loop iteration, not executing all the statements left over.
            break;
        }

        // We know there's still data in the stream, and we want to access it.
        // However, now that the stream is in a "fail" state, we won't be able
        // to read anything.  We can get it back to a good state by clearing the
        // error flags:
        std::cin.clear();

        // We'd like to tell the user what data caused us to fail, and what we
        // ignored.  We're going to do this by reading until the end of the line
        // and stating that anything in there didn't get into our vector.
        std::string s;
        std::getline(std::cin, s); // read a line from std::cin into s

        // Rember how I said line-by-line input and the >> operator don't always
        // mix?  That's because of how the >> operator deals with whitespace.
        // If it read something from the stream, it will leave all the
        // whitespace after it still in there.  That means that when you enter 5
        // and press enter, >> will read the five and leave the newline.  When
        // we then do a getline, that newline will be the "end of the line", so
        // we won't get a chance to enter any new data.
        //
        // Here, we can mix the two because we're reading after a >> attempt
        // failed.  That means that it already got through all the whitespace
        // and what's next is data we may be interested in.  This means we won't
        // be telling the user about how we ignored empty lines.

        std::cout << "Warning, ignoring: " << s << "\n";
    }

    // We've read all the input we possibly could.  Let's thank the user and
    // return the values to the rest of the program.
    std::cout << "End of file encountered, stopping input.\n";
    return result;
}

// Well, that was a mouthful!  However, in all the programs we write from this
// point on, we won't have to repeat this code.  The details will come in the
// next chapter; for now, let's take a look at a few more functions.

/* The function we wrote above allows us to execute a block of code from
 * wherever we want and have it give us back a value.  What we'll do now is
 * parametrise that block of code by a value.  That is, we'll make the function
 * accept values from the caller.  Those values are copied, so setting them only
 * changes what the function sees, not what the caller sees.  However, this also
 * means the function has full freedom to do what it wants with them, without
 * anyone ever finding out.
 *
 * For a function to accept parameters we have to expand our syntax a little:
 *
 *      return_type function_name(param_type1 param1, param_type2 param2 ...) {
 *          statements...
 *      }
 *
 * Parameters are like local variables, but their value is specified from
 * outside the function.  Suppose we define
 *
 *      int square(int x) {
 *          return x*x;
 *      }
 *
 * we have a function square that we can call with an int; for example square(5)
 * would be a valid call.  square would be executed with x initialised to 5, and
 * after it has returned x*x, the original square(5) would evaluate to 25.
 *
 * Recall that we can declare a function by omitting the body (statements and
 * braces) and putting a semicolon after the list of parameters.  Let's first
 * declare some functions and define them later.
 */

// Function that, given a vector, returns the average of the elements.
int average(std::vector<int> v);
// Function that, given a vector, returns the sum of the elements.
int sum(std::vector<int> v);
// Function that, given a vector and int, returns a vector of all elements
// greater than the given int.
std::vector<int> filter_greater_than(std::vector<int> v, int x);

int main() {
    // We already know read_int_vector will give us an std::vector<int>, and the
    // compiler knows that, too.  Writing it out explicitly wouldn't tell anyone
    // anything new, so we use auto and the compiler will assume that v is the
    // type of whatever read_int_vector gave us.
    auto v = read_int_vector();

    // We've declared average, sum, and filter_greater_than so we can use them,
    // even though they haven't yet been defined.  This is one of the powerful
    // things about declarations; we can worry about the definitions much, much
    // later.
    std::cout << "Average: " << average(v) << "\n";
    std::cout << "Sum: " << sum(v) << "\n";

    // We can use the return value of filter_greater_than in a range-based for.
    // Note that there's no easy way of rewriting this to be a normal for loop.
    std::cout << "Elements greater than 5:";
    for (auto e : filter_greater_than(v, 5))
        std::cout << " " << e;
    std::cout << "\n";

    return 0;
}

// While we can put off writing the definitions, we do have to do it eventually.
int average(std::vector<int> v) {
    // The average of a number is the sum divided by the number of elements.
    // Let's define the average of an empty vector to be 0; this makes some
    // sense, and means we don't have to check for empty vectors so often.
    if (v.empty())
        return 0;

    // Notice that we can write this function without writing any loops.
    // They're still there in the compiled program, but we as the programmer
    // don't need to explain how to get the sum of a vector every time we want
    // it.
    //
    // As we've seen before, the type of v.size() is std::size_t.  We want the
    // result to be an int, so we create an int out of v.size() before using it.
    int size = v.size();
    return sum(v)/size;
}

int sum(std::vector<int> v) {
    // We've done this before, and it's not hard.  It's also the last time we'll
    // have to do it explicitly again!
    int total = 0;
    for (auto e : v)
        total += e;
    return total;
}

/* Now that we've gotten to parameter passing and looked at how it works in
 * practice, let's take a look at how it works and what is and isn't allowed.
 *
 * First of all, there's the question of scope.  If you define a variable inside
 * an if clause, while loop, or for loop, you will not be able to use it outside
 * it.  The same thing works with functions: a variable defined in a function
 * stays within that function.  If you want a value from one function to end up
 * in another function, then the only ways we know of so far are by passing it
 * as a parameter or by returning it.  Notice that the functions are so isolated
 * it may even appear like we're breaking the one-definition-only rule: all
 * three of main, average and sum define a variable v!
 *
 * The reason this is allowed is that those three variables, even though they
 * all have the same name, reside in different functions and so are entirely
 * distinct.  They don't know about each-others' existence, can't change each
 * others' data, and we could rename any of the three with no effect on the
 * rest.  In this particular program they all have the same value, but that is
 * coincidental.
 *
 * By the way, saying that there are three of them is not entirely correct.
 * Every time you call a function, all of the variables used inside it are
 * created, and when the function is complete they are destroyed.  When main
 * calls sum and passes it v, the v and total in sum are created, total is
 * changed, its value is returned, and both v and total are again destroyed.
 *
 * When average calls sum and passes it its v, the process happens again.  This
 * isn't particularly efficient, as we end up calculating the sum twice.  Even
 * worse, we end up copying the vector every time we pass it to a function!  We
 * will see how to make this less slow later; for now, understanding functions
 * is much more important than writing blazing-fast code.
 *
 * The way independent variables are created and destroyed every time a function
 * is called is best illustrated with recursive functions: functions that call
 * themselves.  Some problems naturally have significantly more elegant
 * recursive solutions than iterative ones.
 *
 * TODO: Add a fitting example.
 */

std::vector<int> filter_greater_than(std::vector<int> v, int x) {
    std::vector<int> result;
    for (auto e : v)
        if (e > x)
            result.push_back(e);
    return result;
}

/* The next few chapters will be about some practical aspects of using
 * functions and some nuances in the rules regarding them.
 *
 * Functions are important.  So far, these chapters have been fairly low-level
 * and focused on getting you acquainted with the basic syntax.  Make sure you
 * are comfortable with all of these: we're now going to spend some time looking
 * at what we can do with the current tools, what the standard library has to
 * offer us, and what new features we'd like to have.
 */



