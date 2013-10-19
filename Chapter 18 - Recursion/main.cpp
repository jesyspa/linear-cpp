/* Suggested reading order: main.cpp (beginning), parser.hpp, parser.cpp, main.cpp
 * (rest)
 *
 * The tokens and lexer have not changed.
 *
 * We now have a lexer, and it gives us some (though not perfect) position
 * information, so let's implement a simple parser on top of it.  At the moment,
 * we don't have any tools to store the tree, so we'll start by simply
 * recognizing the structure and pretty-printing it back with some annotations.
 * To be specific, we'll take
 *
 *      (+ (* 5 x) 3)
 *
 * and print
 *
 *      function call:
 *          function:
 *              name: +
 *          arguments:
 *              function call:
 *                  function:
 *                      name: *
 *                  arguments:
 *                      number: 5
 *                      name: x
 *              number: 3
 *
 * Take a look at parser.hpp to see the interface.
 */

#include "parser.hpp"
#include <iostream>
#include <sstream>


int main() try {
    /* Up to now we've been reading all standard input and then writing
     * everything to standard output.  We could do this again, but we'd much
     * rather be able to enter an expression on a single line and then
     * immediately get the pretty-printed version.
     */

    // We need a variable to store the current line in.
    std::string line;

    // This extracts a line from std::cin into line, and then returns std::cin
    // so that we can check whether we've hit the end of file yet or not.
    while (std::getline(std::cin, line)) {
        // We now have a string that we would like to parse, but our parser
        // expects an std::istream&.  Fortunately, the standard library has an
        // std::istringstream class that can be treated as an istream, and
        // allows us to store an arbitrary string in it.
        std::istringstream line_stream(line);

        // We could just call parse_and_reprint_expression, but that would
        // terminate the program if the expression was invalid.
        //
        // Recall the semantics of an exception.  A throw indicates that the
        // program has entered an invalid state, and a catch sets it back into a
        // valid state it can continue from.  If it wasn't possible to parse a
        // line of input, we can just notify the user of this and then continue
        // with the next line, so we add a catch and do exactly that.
        try {
            parse_and_reprint_expression(line_stream);
        }
        catch (std::exception& e) {
            // Notice that we're catching more than strictly necessary here.
            // We're almost at the point where this can be fixed.
            std::cerr << e.what() << "\n";
        }
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

/* The next chapter will introduce two important C++ features: inheritance and
 * pointers.  We'll look at how we can represent a tree with nodes of different
 * types, and how we can then use virtual functions to perform operations on the
 * tree.
 *
 * After that, we'll go back and refactor the resulting code.  I've already
 * mentioned many of the issues as we came across them: the longer we keep them
 * in, the more of a pain they will be as we continue, so we'll invest some time
 * into weeding them out.
 */
