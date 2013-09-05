/* Recommended read order: main.cpp (beginning), io.hpp, math.hpp, math.cpp,
 * main.cpp (end)
 *
 * In this chapter, we're going to look at an approach to dealing with errors:
 * namely, exception handling.
 *
 * Let's first recap the way we've already seen though: error flags.  We've seen
 * that when we use an istream and a read fails, it is set to a fail state,
 * which we can then check for.  We can query it for whether the failure was
 * caused by invalid input or by there not being any more input to read,  and
 * then clear the errors once we're ready to continue.
 *
 * Notice that nobody forces us to check the error flags.  In chapter 2, we
 * skipped that step, because we didn't know about if statements yet.  We have
 * been doing it systematically since then, but only for std::cin: we've never
 * checked whether our output to std::cout would work, just assuming that
 * everything would be fine.  If anything ever did go wrong, our program would
 * never notice.
 *
 * Exceptions take a different approach to the problem.  They split the work
 * between two pieces of code: the thrower and the catcher.
 *
 * The thrower is the code that reports an error.  It looks almost like a return
 * statement:
 *
 *      throw expression;
 *
 * The expression is evaluated, and its value becomes the exception.  Just like
 * when you return a value the function doesn't continue as normal, throwing a
 * value breaks the normal flow of control.  Instead of continuing with the next
 * statement, the program looks for a catcher.  If none is found in the current
 * function, the function that called this one is looked at; and so on, until
 * we've found a catcher or checked main and found that nobody is willing to
 * handle our error.
 *
 * The catcher is the code that claims to be able to deal with the error.  It
 * looks like this:
 *
 *      try {
 *          throwing statements...
 *      }
 *      catch (type x) {
 *          handling statements...
 *      }
 *      catch (other_type x) {
 *          other handling statements...
 *      }
 *
 * The catcher specifies some potentially throwing statements by putting them in
 * a try clause.  It then lists at least one catch clause: the word catch,
 * followed by what looks like a parameter list, but it's limited to one
 * parameter.  The type of that parameter is used to know what exceptions we
 * want to catch.
 *
 * When an exception is thrown, its type is remembered.  A catcher is found, and
 * then its catch clauses are inspected from top to bottom.  If any of them have
 * a suitable type, that catch clause is run and the statements in there should
 * handle the error.  If we've checked all catchers up to main and nobody is
 * willing to handle this type of exception, the program terminates.
 *
 * We can see this system as one of passing around responsibility.  When you
 * call a function, you make it responsible for computing a certain value.  If a
 * function cannot do that, it can throw an exception.  It loses its
 * responsibility (and thus also its right to keep executing), and we look at
 * each caller in turn to see who is willing to accept this responsibility.
 * Whoever does has his handler code run.  If nobody does, no code is run, and
 * your program grinds to a halt.
 *
 * Go ahead and look at io.hpp for an example involving streams.
 */

#include "io.hpp"
#include "math.hpp"

// When an entire function is a catcher, we can use a so-called function try
// block.  In this case, it's a matter of personal preference whether you do it
// this way or just by having a normal try block.  We'll see some cases where
// you can't avoid using it later.
int main() try {
    std::cout << "Enter a: ";
    auto a = read<double>();
    std::cout << "Enter b: ";
    auto b = read<double>();
    std::cout << "Enter c: ";
    auto c = read<double>();

    auto result = find_roots(a, b, c);
    std::cout << "First root: " << result.first << "\n";
    std::cout << "Second root: " << result.second << "\n";

    // Notice how we don't have to do any error-checking here.  It's all done by
    // read and find_roots; if anything goes wrong, an exception will be thrown
    // and we'll catch it below.  We've separated the code that does the work
    // from the code that handles the errors.
}
// Now that we're at our error-handling part, what do we catch?  The two error
// types we threw were std::runtime_error and std::domain_error.  We could write
// individual catch blocks for each, but there's a better solution.
//
// C++ types don't have to be entirely distinct.  A type A can be a subtype of a
// type B; that means that every value of type A also has type B.  We say B is a
// supertype of A.  In this case, std::runtime_error and std::domain_error both
// share a supertype std::exception, so catching std::exception will catch both
// of them.
//
// However, a subtype may say more about the value than the supertype does.  If
// we catch std::exception by value, we will be copying the std::runtime_error
// and std::domain_error, which may lose us data.  Instead, we'll catch it by
// reference: seeing as our value has type std::exception that is allowed, and
// seeing as our reference refers to the original object, no data loss can
// occur.
catch (std::exception& e) {
    // e.what() returns the message we attached to the std::runtime_error or
    // std::domain_error
    std::cerr << "Error: " << e.what() << "\n";
    return -1;
}
// As I said before, we really don't want exceptions escaping main.  We can use
// a catch (...) clause to catch errors of any type.  However, as the value can
// be of any type, it doesn't make sense for us to be able to inspect it; we
// wouldn't know what to do with it!
catch (...) {
    std::cerr << "Unknown error.\n";
    return -1;
}

/* So far, I've been talking about exceptions as an altogether positive
 * solution.  This is not an opinion held by everyone -- you'll find that quite
 * a few people aren't particularly fond of exceptions.
 *
 * Put simply: exceptions are the Hard Mode of C++.  If you're coding with
 * exceptions, a large number of your expressions can throw, meaning that only
 * part of your code will be executed, while the rest will be skipped.  You have
 * to make sure that this isn't a problem.  Again: you have to make sure, for
 * every piece of code, that either it does not (and never will!) throw an
 * exception, or that only part of the code being executed does not corrupt your
 * program state in any way.  You can use catch clauses to fix some things, but
 * we will need more powerful tools to handle all the problems that this brings
 * us.
 *
 * Some examples:
 *
 *      foo();
 *      bar();
 *
 * Up to now, we knew foo would be called, then bar would be called.  In hard
 * mode, there's a chance foo will throw an exception and bar won't be called.
 *
 *      bar(foo());
 *
 * Same as above.  We cannot assume bar will be called, unless we proved some
 * very strong claims about foo.
 *
 *      bar(foo(), faa())
 *
 * Earlier, we knew foo and faa would be called in some unspecified order.
 * After that, bar would be called with the results.  In hard mode, all of these
 * are possible:
 *
 *  - foo called but throws, others never called
 *  - faa called but throws, others never called
 *  - foo called successfully, faa called but throws, bar never called
 *  - faa called successfully, foo called but throws, bar never called
 *  - foo called successfully, faa called successfully, bar called but throws
 *  - faa called successfully, foo called successfully, bar called but throws
 *
 * Let's add another one:
 *
 *      bar(foo(), faa(), fee())
 *
 * We couldn't be sure about what order these would be called in, but we'd knew
 * all three of foo, faa, and fee would be called, and then bar would be.  Now
 * the situation is as above, but with even more options.  Perhaps faa will be
 * called and complete successfully, and then foo will throw, so that fee is
 * never called.  Perhaps things will happen in some other order.  In general,
 * you cannot know, and you'll have a lot of code on your hands if you write a
 * catch clause for every function you call.
 *
 * If exceptions make C++ harder, why use them?  It turns out that making our
 * code exception-safe is often a good idea anyway.  When you have a group of
 * functions that must always be executed together, it generally pays to put a
 * little extra effort into guaranteeing that; even if exceptions don't break
 * it, a careless code change or a change in design might.
 *
 * Besides, it isn't all doom and gloom.  Solutions to many of these problems
 * have been found, and once generalised, they can save effort.  In the end,
 * once the pitfalls have been studied and bridges have been built, the results
 * are better.
 *
 * In my opinion, anyway.
 */
