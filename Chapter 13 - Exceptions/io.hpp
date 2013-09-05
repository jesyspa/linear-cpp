#ifndef CHAPTER_13_IO_HPP
#define CHAPTER_13_IO_HPP

#include <iostream>
#include <stdexcept>

/* We're going to define a function template that reads a value of the type we
 * specify.  If it can't read the value, it'll throw an instance of
 * std::runtime_error.
 *
 * C++ allows us to throw values of most types, but there are types that are
 * specifically designed to be thrown, and we should generally limit ourselves
 * to those.  We will later see how to create our own, which means this will not
 * be a severe limitation.
 */

template<typename T>
T read(std::istream& stream = std::cin) {
    T result;

    // If everything went fine, we return.
    if (stream >> result)
        return result;

    // If we hit the end of file, report that
    if (stream.eof())
        throw std::runtime_error{"read failed; EOF encountered."};

    // otherwise, the input wasn't in the format we expected.
    throw std::runtime_error{"read failed; malformed input."};
}

/* When we call read to take some input, we can't accidentally ignore an error.
 * We can write a catcher that does nothing to explicitly silence it, but if we
 * simply forget to write a catcher, the exception will fly right through our
 * code and out of main.  If that happens, our program will terminate.
 *
 * Let's take a look at math.hpp now, where we'll also use exceptions.
 */

#endif

