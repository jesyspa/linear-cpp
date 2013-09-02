/* Last time we looked at how to accept user input, but we couldn't detect
 * invalid input.  We will introduce a language construct that lets us handle
 * that, but first let's take a quick refresher.
 *
 * So far, we have seen three kinds of statements.  The first we encountered was
 * the return statement.  This let us return a value out of a function.  So far,
 * the only function we've written was main, and we always returned 0; needless
 * to say, we'll see much more of this later on.
 *
 * The second was an expression statement.  This is simply a statement that
 * consists entirely of an expression.  For example,
 *      std::cout << "Hello world!\n";
 * is an expression statement.  Here, std::cout << "Hello world!\n" is an
 * expression, and the semicolon turns the whole thing into a statement.
 *
 * Finally, we had variable definitions like
 *      int x;
 *
 *
 * Now we're going to introduce a fourth kind of statement: the if statement.
 * The syntax is as follows:
 *
 *      if (condition) {
 *          statements...
 *      }
 *
 * The condition is something that results in type bool, and you can have as
 * many statements in the body as you'd like.  If the condition evaluates to
 * true, the statements will be executed; otherwise, we skip to after the if
 * statement.
 *
 * Without further ado, let's get to examples.
 */

#include <iostream>
#include <string>

int main() {
    int x;
    std::cout << "Enter a number: ";
    std::cin >> x;

    // Once we've reach this point, we've made an attempt to read an int.  We
    // can now check whether we were successful.  Streams were made in such a
    // way that we can evaluate them as bools.  If the input succeeded, std::cin
    // will be in a good state and converting it to a bool will give true.  If
    // the input failed, however, std::cin will be set to "fail" and converting
    // it to a bool will give false.  We'd like to report an error if it failed,
    // so we have to invert true and false; this is done with the ! operator.
    // !true == false and !false == true.
    if (!std::cin) { // if std::cin is false
        std::cout << "That's not a number!\n";
        // Once a value has been returned, the function stops executing.  This
        // means that a return in main works as an "early exit" from the whole
        // program.
        //
        // We return 1 to indicate that the program did not complete
        // successfully.  As we will be using this program interactively it does
        // not matter much; however, this is still neater than returning 0 as if
        // everything is fine.
        return 1;
    }

    int y;

    // Recall that std::cout << "Hello" evaluates to std::cout.  Similarly,
    // std::cin >> y will evaluate to std::cin.  We can use this to take input
    // and check whether it succeeded in one step:
    std::cout << "Enter another number: ";
    if (!(std::cin >> y)) { // if reading y fails...
        std::cout << "That's not a number!\n";
        return 1;
    }

    /* There's another neat feature if statements have, and that's that you can
     * specify some code to be executed if the condition is not true.  The
     * syntax is:
     *
     *      if (condition) {
     *          statements...
     *      } else {
     *          other_statements...
     *      }
     *
     * If condition is true, the first statements will be executed; if not, the
     * other ones will be.  Once we're done with whichever statements we are
     * executing we continue with the code after the else clause.
     */

    // We can use this to compare the two values the user entered:
    if (x < y) {
        std::cout << "The first number you entered is less than the second.\n";
    } else {
        if (x == y) {
            std::cout << "The two numbers you entered are equal.\n";
        } else {
            std::cout << "The first number you entered is greater than the second.\n";
        }
    }

    // However, as you can see, we're using a lot of space to say fairly little.
    // When we only have one statement in the if or else block, we can skip the
    // curly braces and just write that one statement instead:

    if (x < y)
        std::cout << "The second number you entered is greater than the first.\n";
    else if (x == y)
        std::cout << "The two numbers you entered are equal.\n";
    else
        std::cout << "The second number you entered is less than the first.\n";

    // Finally, you can combine multiple reads in one condition.
    std::cout << "Enter two numbers: ";
    if (std::cin >> x >> y) {
        std::cout << "You did it right!\n";
    } else {
        std::cout << "Something you entered wasn't a number.\n";
    }

    // Whether we use curly braces here or not is a matter of personal
    // preference.

    return 0;
}

