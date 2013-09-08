/* Suggested reading order: main.cpp (beginning), token.hpp, lex.hpp, lex.cpp,
 * main.cpp (rest)
 *
 * We've seen how we can print the tokens present in a stream.  Now, instead of
 * simply outputting the tokens we'd like to return them.
 *
 * First of all, we'd like to have a name for each kind of token: name_token,
 * open_paren_token, close_paren_token, number_token, and end_of_file_token.  We
 * don't really care what the type of these is, as long as we can assign them
 * and compare them for equality.
 *
 * Once we have that, we'd like Token to be a type.  If tok is an instance of
 * token, we want tok.type to be the type of token tok is, and tok.value to be
 * the string associated with tok.
 *
 * Proceed to token.hpp and we'll take a look at how we can create such a type.
 */

#include "lex.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

void print_token(Token const& tok) {
    std::cout << "{ ";

    // This chain of ifs and elses doesn't look particularly good.  We'll see
    // how we can make it better later on.
    if (tok.type == open_paren_token)
        std::cout << "open_paren_token";
    else if (tok.type == close_paren_token)
        std::cout << "close_paren_token";
    else if (tok.type == name_token)
        std::cout << "name_token";
    else if (tok.type == number_token)
        std::cout << "number_token";
    else if (tok.type == end_of_file_token)
        std::cout << "end_of_file_token";

    std::cout << ", \"" << tok.value << "\" }\n";
}

int main() try {
    std::vector<Token> tokens;
    while (std::cin)
        tokens.push_back(extract_next_token(std::cin));

    std::for_each(tokens.begin(), tokens.end(), print_token);
}
catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return -1;
}
catch (...) {
    std::cerr << "Unknown error.\n";
    return -1;
}

/* We can now operate on tokens from inside the program.  It is tempting to
 * immediately continue to parsing and tree-construction, but there's no need to
 * rush.  There are a number of places where the current implementation is
 * suboptimal and we should take a look at those before we move on to more
 * advanced matters.
 *
 * In particular, we can make it possible to compare tokens using == and != and
 * input and output them using >> and <<.  We can also make print_token neater
 * and finally get a proper introduction to the name::other_name syntax that
 * we've been using without a proper explanation for far too long.
 */
