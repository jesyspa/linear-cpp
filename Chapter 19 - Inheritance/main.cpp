/* Suggested reading order: main.cpp (beginning), expression.hpp,
 * number_expr.hpp, variable_expr.hpp, list_expr.hpp, parser.hpp, parser.cpp,
 * number.cpp, variable.cpp, call.cpp, main.cpp (rest)
 *
 * We've already seen that every object in C++ must have a type.  We'd like to
 * make an Expression type that can represent any kind of expression we can
 * parse.  However, there's no single representation of an Expression: it might
 * be a number, or a variable name, or a list of other expressions.  We could
 * go the same route as we went with Token, adding an int to keep track of what
 * kind of expression we're working with; while this would work, it would
 * involve reserving space for all three possibilities, and we'd have to be
 * extra careful about which possibility we are currently in.
 *
 * Instead, we'll have the Expression type which will only define what must be
 * possible to do with an expression; it won't define how that expression is
 * represented, or how the operations are implemented.  Each of the three kinds
 * of expressions we saw will then get their own, distinct type, but will
 * inherit from the common Expression type.  The compiler will enforce that they
 * define the operations we left undefined in Expression, and we will be able to
 * treat them as if they were Expressions.  In particular, we will be able to
 * make a reference to an Expression that actually refers to an instance of one
 * of the derived types.
 *
 * Take a look at expression.hpp to see how it is implemented.
 */

#include "parser.hpp"
#include <iostream>
#include <sstream>


int main() try {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream line_stream(line);

        try {
            auto ptr = parse_expression(line_stream);
            // Recall the operator<< overload in expression.hpp; thanks to that,
            // we can put this here.
            std::cout << *ptr << '\n';
        }
        catch (std::exception& e) {
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

/* And that's our parser!  Note that the representation we chose for our
 * expressions is neither the only possible nor necessarily the best one; it is
 * simple and illustrates some important concepts, which is why I chose it for
 * the moment.
 *
 * Even given this representation, there's often better ways of doing things.
 * For one example, take a look at
 *   http://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
 *
 */
