/* Suggested reading order: main.cpp (beginning), lexer.hpp, lexer.cpp, main.cpp
 * (rest)
 * token.hpp and token.cpp have undergone minor changes: operator>> is gone, and
 * operator<< works as print_token did in chapter 15.
 *
 * Now let's take a closer look at how we read tokens.  In practice, just being
 * able to extract tokens one by one often isn't good enough: we want to track
 * position information, look a few tokens ahead or behind, and all that without
 * caring about how it is implemented.
 *
 * The solution that comes to mind with the tools we have so far is to make a
 * type Lexer that contains all the necessary data, and then write a bunch of
 * functions that take it by reference and update the state.  This would work,
 * but there's two big issues with it:
 *
 *  - Having to always explicitly pass around our Lexer would get tedious.  We
 *    already have this problem with passing the std::istream& around to our lex
 *    functions; this would make it worse.
 *  - There's no easy way to specify what is part of the public interface and
 *    what is an implementation detail.  We may want to keep a vector of parsed
 *    tokens, but we don't want people to write code relying on that vector;
 *    what if we later decide to use a different data structure for it?
 *
 * We will still create a Lexer type, but we will avoid both of the above issues
 * using member functions.  Take a look at lexer.hpp.
 */

#include "lexer.hpp"
#include <iostream>


int main() try {
    Lexer lex{std::cin};
    while (lex) {
        // We report the positions one past the end of tokens, not the starting
        // ones.  There's a number of ways to change this, the simplest being to
        // make the position part of the token data, but it doesn't matter much
        // for the example.
        auto tok = lex.extract();
        auto pos = lex.get_position();
        std::cout << pos << " " << tok << "\n";
    }
}
catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return -1;
}
catch (...) {
    std::cerr << "Unknown error.\n";
    return -1;
}

/* The main thing to take away from this chapter is that when we have a type,
 * there's a nice syntax for defining functions that operate on this type.  We
 * will use member functions extensively from now on: for now they are easily
 * rewritten as normal functions that take an extra reference parameter, but
 * we will see usages where the conversion isn't quite as simple.
 *
 * Spend some time writing your own types.  There's quite a few improvements
 * that can be made to the lexer class: the position information could be made
 * more precise, and we could make things more efficient.  These things are not
 * hard to fix, but add more complexity, which is why I did not include them.
 *
 * A bigger issue is the fact that Lexer is doing a little too much: it handles
 * position information and token retrieval all at once.  It would have been
 * better if the Lexer only had to implement the extraction functions, and a
 * separate StreamWithPosition type would deal with the rest.  See if you can
 * come up with a neat way of splitting the two.
 *
 * By the way, as mentioned in lexer.hpp, both the struct and class keywords can
 * be used to define a type.  I'll use "struct" and "class" interchangably when
 * referring to types we define; just "type" is a more generic term, as int is
 * also a type
 */
