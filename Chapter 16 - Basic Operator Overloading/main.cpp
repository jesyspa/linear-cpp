/* Suggested reading order: main.cpp (beginning), token.hpp, token.cpp, main.cpp
 * (rest)
 * lex.hpp and lex.cpp have not changed.
 *
 * We now have a Token type that we can use to represent tokens in our program.
 * At the moment, we can create Tokens, pass them to and from functions, and
 * access the type and value members.  However, given two tokens x and y, we
 * cannot do x == y or x != y, and we cannot output a token with std::cout << x,
 * nor read one with std::cin >> x.  In this chapter we'll fix those issues.
 *
 * In order to make those operations legal, we need to define how those
 * operators work when given Tokens.  Just like functions, operators take
 * parameters and give a result, so it comes as no surprise that overloaded
 * operators are actually functions written with nicer syntax.  The name of the
 * function is operator@@, where @@ is the operator in question.
 *
 * (BUG: At the moment, there is no mention of overloading up to this point.
 * This should probably be handled at least briefly before operator overloading
 * comes to play.  I can't think of where to put it, though.)
 *
 * Go to token.hpp for some examples.
 */

#include "lex.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

int main() try {
    // There are no implicit conversions to string happening here: the >> and <<
    // operators really are taking Tokens.
    Token tok;
    // Notice that this way of reading means we never see the end_of_file_token.
    // This is just for demonstration purposes; soon we'll have a better way to
    // do this.
    while (std::cin >> tok)
        std::cout << tok << "\n";
}
catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return -1;
}
catch (...) {
    std::cerr << "Unknown error.\n";
    return -1;
}

