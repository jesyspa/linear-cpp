/* Suggested reading order: ...
 *
 * Now that we know how to print expressions, it's not a big step to evaluate
 * arithmetic expressions and print their results.  We'll do this by adding a
 * second virtual member function to Expression which will perform whatever
 * operation we want it to and then return the result as an int.
 *
 * What work has to be done to evaluate an expression depends on its form.  If
 * we have a number, we can simply return it as-is; it's already as evaluated as
 * it can be.  If we have a list, we want to treat it as function application.
 * Suppose we wanted to evaluate
 *
 *     (+ 1 (* 2 3))
 *
 * We would like this to evaluate as 1 + (2 * 3); that is, to 7.  We do this by
 * evaluating all but the first element of the list, and then using the first
 * element to decide what operation should be performed.  In pseudocode:
 *
 *     eval (f arg1 arg2 arg3...) == f (eval arg1) (eval arg2) (eval arg3)...
 *
 * What do we do when we encounter a variable name?  At the moment, our system
 * is too simple to handle this case, so we'll throw an exception.
 *
 * Note that the first element of each list is special, in that it does not get
 * evaluated.  Instead, we will assume that it is a variable and use the value
 * of that to choose what operation to perform.  We'll need a way of mapping
 * strings to functions.
 *
 * [Note: std::maps were not yet covered, but this is an oversight.  A chapter
 * will be added to the beginning to introduce them properly.  The five-minute
 * explanation is that a map is a container which associates keys to values.
 * That means that an object of type std::map<Key, Value> will let you look up
 * what Value corresponds to some Key easily.  For example, we can have a map
 * from strings to ints:
 *
 *     std::map<std::string, int> map;
 *     map["hello"] = 5; // automatically creates a "hello" element
 *     std::cout << map["hello"] << '\n'; // prints 5
 *
 * If the element is not yet in the map, it will be constructed and initialized.
 * That means that for class types the constructor will be run, and for built-in
 * types they will get their corresponding zero value.]
 *
 * We don't want to restrict the number of elements in the list, so our
 * functions should take a vector of arguments.  We're only working on ints at
 * the moment, so the function will look as follows:
 *
 *     int builtin_add(std::vector<int> const& args);
 *
 * The type of the above is int(std::vector<int> const&).  The C++ standard
 * library provides the std::function template which we can use to store
 * anything that can be used like a function with a certain type.  This means
 * we can represent each of our operations as an object of type
 *
 *     std::function<int(std::vector<int> const&)>
 *
 * We can then represent the whole symbol table as an object of type
 *
 *     std::map<std::string, std::function<int(std::vector<int> const&)>>
 *
 * A bit of a mouthful, but this structure will come in useful often in the
 * future.
 *
 */

#include "parser.hpp"
#include "builtin_operations.hpp"
#include "symbol_table.hpp"
#include <iostream>
#include <map>
#include <sstream>


int main() try {
    auto symbol_table = get_default_symbol_table();
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream line_stream(line);

        try {
            auto ptr = parse_expression(line_stream);
            std::cout << ptr->evaluate(symbol_table) << '\n';
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
