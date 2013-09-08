#ifndef CHAPTER_15_TOKEN_HPP
#define CHAPTER_15_TOKEN_HPP

#include <string>

/* Let's start by defining the token types.  We'll make them int consts; we will
 * see a better solution soon, but this will do until we've had a chance to
 * introduce that.
 *
 * There's two reasons to make them const here: the first and most important one
 * is that it makes no sense for anyone to modify them: after all, they're just
 * tags and their values, as long as they're all different, don't really matter.
 *
 * The other reason is that marking them const means we can define them in the
 * header.  Had they been normal ints this would lead to double definition
 * errors, but because the type is const they are excluded from that rule and
 * may be defined multiple times in different translation units, as long as the
 * definitions are all the same.
 */

/* By the way, yes, you are allowed to define arbitrary variables outside
 * functions.  However, doing so is a sure way to make your project a tangled
 * mess.  Chances are that if you wanted to do this, the features of structs
 * we'll be looking at shortly will provide a better solution.
 */

int const open_paren_token = 0;
int const close_paren_token = 1;
int const name_token = 2;
int const number_token = 3;
int const end_of_file_token = 4;

/* With that out of the way, we can look at creating the Token type.  The syntax
 * for that is, very roughly:
 *
 *  struct name {
 *      members...
 *  } instances...;
 *
 * For now, members are just variable declarations; they'll become much more as
 * we progress, but there's no need to worry about that for now.  instances are
 * an interesting historical curiousity.  They allow us to immediately define
 * variables of the type we just defined.  You won't see them used all that
 * often, but knowing that they're allowed explains why you need a semicolon at
 * the end of your struct definition.
 *
 * Now, our Token type:
 */

// We wanted the name to be Token, and we wanted tok.type and tok.value to be
// available.
//
// Note that we use int for type, even though open_paren_token and friends are
// all int const.  Note that when we say tok_a = tok_b, we overwrite tok_a's
// type and value members.  If we were to use int const here, that overwrite
// would be illegal and we wouldn't be able to assign Tokens to each other.
struct Token {
    int type;
    std::string value;
};

/* Note that I did say struct *definition*.  struct declarations exist, too: if
 * we wanted to only declare Token and not define it, we could have said
 *
 *  struct Token;
 *
 * However, Token would be a so-called incomplete type, meaning we couldn't make
 * instances of it or use any members; after all, we don't know which ones it
 * has.
 *
 * Why are we allowed to put a struct definition in a header?  This is yet
 * another case of multiple definitions being allowed in different translation
 * units if they are identical.  The definition of Token is something that most
 * code that uses Token needs, so it would be very impractical if we could only
 * define it in one translation unit.
 *
 * Continue to lex.hpp.
 */

#endif
