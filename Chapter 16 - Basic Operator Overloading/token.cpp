// A minor detail: here we use the fact we split token and lex into header and
// source files.  This means we can have both source files include both header
// files, and everything will work fine.  Had we not split them this way, we
// would have to first have to include everything declared and defined in token,
// and then everything defined in lex, or the other way around.  Try rewriting
// the program like that, and see where you run into issues.
#include "token.hpp"
#include "lex.hpp"

/* The definitions are just as close to function definitions.  The syntax is
 * new, but conceptually these are all things we could have written normal
 * functions for before.
 */

bool operator==(Token const& lhs, Token const& rhs) {
    return lhs.type == rhs.type && lhs.value == rhs.value;
}

bool operator!=(Token const& lhs, Token const& rhs) {
    // We could repeat the logic here, but defining it in terms of operator== is
    // simpler.
    return !(lhs == rhs);
}

std::istream& operator>>(std::istream& is, Token& tok) {
    // We already have extract_next_token, so there's no need to reimplement all
    // that functionality.
    //
    // If the stream is already in a failed state we don't want to modify tok.
    if (is)
        tok = extract_next_token(is);
    return is;
}

/* We could use the print_token code here, and the compiler would have no issue
 * with it.  However, we are used to the >> and << operators being symmetrical:
 * if we have defined each, it would be nice if reading using >> and then
 * writing using << would return similar results.
 *
 * In the case of tokens, this isn't particularly convenient: printing them is
 * mostly intended for debugging, and then we want to have full information
 * about each token.  In the next lesson we'll look at a more elaborate lexer
 * which will replace both extract_next_token and operator>>, and then we'll
 * define operator<< as we like it.
 */
std::ostream& operator<<(std::ostream& os, Token const& tok) {
    os << tok.value;
    return os;
}
