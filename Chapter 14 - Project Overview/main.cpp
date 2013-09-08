/* Over the next few chapters, we'll be writing a simple lexer, parser, and
 * interpreter for a LISP-like language.
 *
 * Many of the features of C++ are intended for larger programs.  While they
 * could all be demonstrated in smaller examples, I expect this to do nothing
 * but obscure the purpose of the thing.
 *
 * Let's take a high-level overview of the project:
 *  - First we'll want to write some code that we can use to split the input
 *  into logical chunks, skipping anything we're not interested in (like
 *  whitespace).  We don't need anything new for that, so this chapter will
 *  cover it fully.
 *  - We'll then want to be able to store these chunks, which we'll call tokens.
 *  A number of chapters will be spent on improving the representation.
 *  - Working directly with the sequence of tokens would be inconvenient, so we
 *  write a helper to automate the common tasks.
 *  - Once we can work with the tokens easily, we'll write a function that can
 *  analyze the structure in order to make a tree.  We'll see the details later.
 *  - We'll spend some time looking at how we can represent homogenous and
 *  heterogenous trees, and how we can perform computations over them.
 *  - Some implementation details like symbol tables may need more attention.
 *  - Finally, we'll put everything together to make both an interpreter for
 *  files and a REPL.
 *
 * If you've never seen Lisp before, it looks roughly like this:
 *
 *  (+ (* 2 2) 3)
 *
 * In C++, this expression would look like
 *
 *  (2*2) + 3
 *
 * We can also define variables:
 *
 *  (define x 5)
 *
 * and have so-called lambda-functions
 *
 *  (lambda (x) (* x x))
 *
 * the above is a function that takes a single parameter x and returns x*x.
 *
 * We'll also support the -, /, ==, !=, <, <=, >, >= operators and an if
 * function.  This means the factorial function can be written as:
 *
 *  (define factorial
 *          (lambda (x)
 *                  (if (<= x 1)
 *                      0
 *                      (* x (factorial (- x 1))))))
 *
 * Translated to C++, the above is almost exactly the same as
 *
 *  int factorial(int x) {
 *      if (x <= 1)
 *          return 0;
 *      else
 *          return x * factorial(x-1);
 *  }
 *
 * Leaving aside the question of which one looks better, we can guess that the
 * Lisp version is going to be much easier to write a program to evaluate.
 *
 * We have five kinds of tokens:
 *  - opening parentheses
 *  - closing parentheses
 *  - operators (sequences of +*-/!=<>)
 *  - names (sequences of letters)
 *  - numbers (sequences of digits)
 *
 * However, notice that we can use operators and names interchangably.  This
 * means that we don't have to make a separate category for them.  We end up
 * with four categories: open_paren, close_paren, name and number.
 *
 * It also helps to have a special token type for the end of the file.  This
 * serves a double purpose: it means we know when to stop asking for more
 * tokens, and it lets us check that all input has indeed been handled.  Seeing
 * as we're just printing the tokens for now it may not seem like that big a
 * difference, but by the next chapter we'll be glad we did it.
 *
 * Apart from knowing that a name or number was seen, we'd also like to know
 * what name or number it was.  This means that every token should have an
 * associated string.  For opening and closing parentheses this could be
 * omitted, as they are always the same, but doing so at this point would be
 * more trouble than it's worth.
 *
 * All in all, we want a program that can take
 *
 *  (+ foo 24)
 *
 * And print
 *
 *  { open_paren: "(" }
 *  { name: "+" }
 *  { name: "foo" }
 *  { number: "24" }
 *  { close_paren: ")" }
 *  { end_of_file: "" }
 *
 */

#include <string>
#include <iostream>
#include <cctype>
#include <stdexcept>

// As usual, we'll split our program into a few functions.

// Does exactly what it says on the tin and is our main "driving" function.
// All the other parsing functions are called from here.
void print_next_token(std::istream& stream);

// Let's get the implementation of main out of the way before we look at more
// specific things.
int main() try {
    while (std::cin) {
        print_next_token(std::cin);
        std::cout << "\n";
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

// Well, that was quick and painless.  Now on to the less painless parts:

// We'll use helper functions for lexing the non-trivial symbols.  The simpler
// ones can go right in print_next_token.
void lex_name(std::istream& stream);
void lex_number(std::istream& stream);
void lex_operator(std::istream& stream);

// Let's write a function to check for tokens that are allowed in operators.
bool isoperator(char c) {
    // std::string's find returns the position of the character, or
    // std::string::npos if the character isn't found.
    std::string const valid_chars = "+*-/!=<>";
    return valid_chars.find(c) != std::string::npos;
}

void print_next_token(std::istream& stream) {
    // We want to parse the input character-by-character.  We'll store the
    // character we're currently parsing in c
    char c;
    // Here's a loop somewhat unlike what we've seen before -- instead of a body
    // it's just got a semicolon after it.  That's allowed: the semicolon is an
    // empty statement, which is a valid body.  You can read this as "while the
    // condition is true, do nothing".
    //
    // Why is this useful?  Our condition is what's doing the work.  The &&
    // operator is defined to first evaluate what's on the left of it, and only
    // if that is true will the right-hand side ever be evaluated.
    // stream.get(c) is true if and only if it managed to extract a character
    // into c.  After that, we use std::isspace to check whether that character
    // is a space.  This means that characters will keep getting extracted as
    // long as they're whitespace, and once the loop is done, either we've read
    // all the input we had or c is a non-whitespace character.
    while (stream.get(c) && std::isspace(c));

    // Now that we've ignored the spaces, we can check whether there's anything
    // more to parse:
    if (!stream) {
        std::cout << "{ end_of_file: \"\" }";
        return;
    }

    // We can check if the character is a parenthesis...
    if (c == '(') {
        std::cout << "{ open_paren: \"(\" }";
        return;
    }
    if (c == ')') {
        std::cout << "{ close_paren: \")\" }";
        return;
    }

    // If it isn't any of the above, it must be a name or number.  We've
    // declared functions for parsing those three things already, so we just
    // need to select the right function.  However, those functions don't take a
    // char for the first symbol, which we've already extracted, so if we just
    // called one of them with the rest of the stream, we would end up skipping
    // over the first character of whatever we were parsing.
    //
    // To fix this we "unget" the character we extracted.  We can still use c,
    // as its value won't be changed by this, but now our lexing functions will
    // see the whole token.
    stream.unget();

    if (std::isalpha(c))
        lex_name(stream);
    else if (std::isdigit(c))
        lex_number(stream);
    else if (isoperator(c))
        lex_operator(stream);
    else // we couldn't recognise the character
        throw std::runtime_error{"unrecognised character"};
}

// Now let's write our lexing functions
void lex_name(std::istream& stream) {
    char c;
    std::string name;
    // This is similar to the whitespace-clearing loop above, but now we store
    // the character in a string.  Pushing-backing into a string works just like
    // it does with a vector.
    while (stream.get(c) && std::isalpha(c))
        name.push_back(c);
    // We don't want the last character we extracted to disappear.
    if (stream)
        stream.unget();

    std::cout << "{ name: \"" << name << "\" }";
}

void lex_number(std::istream& stream) {
    char c;
    std::string number;
    while (stream.get(c) && std::isdigit(c))
        number.push_back(c);
    if (stream)
        stream.unget();

    std::cout << "{ number: \"" << number << "\" }";
}

void lex_operator(std::istream& stream) {
    char c;
    std::string op;
    while (stream.get(c) && isoperator(c))
        op.push_back(c);
    if (stream)
        stream.unget();

    std::cout << "{ name: \"" << op << "\" }";
}

// Tada!  Notice how similar lex_name, lex_number and lex_operator are.
// Eventually we'll be able to make these things less similar.

/* We can now recognise different tokens.  Next we'll look at how we can
 * represent these tokens inside the program so that we can pass them to and
 * from functions and make vectors of them.  You can probably guess that
 * std::pair<std::string, std::string> would do the job, but C++ offers a
 * neater solution.
 */
