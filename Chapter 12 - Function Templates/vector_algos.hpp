#ifndef CHAPTER_12_VECTOR_ALGOS_HPP
#define CHAPTER_12_VECTOR_ALGOS_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <numeric>

/* A template of a function allows us to write a function and then specify some
 * of the types later.  When we specify the types, a specific instantiation of
 * the template will be created, with the blanks for the types filled in.  Note
 * that a template of a function is not itself a function: it is a recipe for creating
 * a function.
 *
 * Because of this, you can't simply declare the template in a header and then
 * define it in a source file.  If we tried, the compiler wouldn't know how to
 * create an instantiation for a specific type, and would assume that it has
 * been explicitly created elsewhere.  This can work sometimes, but the "normal"
 * way is to define templates in headers.
 */

/* How do we define a function template, anyway?  We start out be specifying
 * how many types we're generalising over; listing the parameters of the
 * template, just like we'd normally list the parameters of the function:
 *
 *      template<typename T1, typename T2...>
 *
 * After we've written that, we write a function as normal.  However, we can use
 * T1 and T2 from above as types.  As a very simple example, we may write
 *
 *      template<typename NUM>
 *      NUM add(NUM x, NUM y, NUM z) {
 *          return x + y + z;
 *      }
 *
 * When we want to call our function template, we provide the type arguments to the
 * template between < and > angle braces, just like we did with std::vector.  If
 * we want to use add with NUM being int, we say:
 *
 *      add<int>(5, 6, 7)
 *
 * The resulting code will probably be (almost) the same as if we wrote
 *
 *      int add_int(int x, int y, int z) {
 *          return x + y + z;
 *      }
 *
 * and then called add_int(5, 6, 7).  However, the template version lets us say
 *
 *      add<double>(2.71, 3.14, 9.9)
 *
 * and even (adding two std::strings concatenates them)
 *
 *      add<std::string>("Hello ", "World", "!")
 *
 * Notice that in add<int>(5, 6, 7) all parameters have type int.  This lets the
 * compiler guess that we want to use the int version, and so we can simply call
 *
 *      add(5, 6, 7)
 *
 * and the template arguments will be deduced.  The same works for the double
 * example.  Unfortunately, it breaks down in the last example: string literals
 * aren't of type std::string, so the deduction would not be correct.
 *
 * Let's take a look at how our functions look when rewritten to function
 * templates.
 */

// T is a very common name to use for template parameters.  Here, we still want
// to read an std::vector, but we want to allow vectors of types other than int.
//
// We use a single parameter to take the place of int, and then replace all
// int-specific code with code that works with T.  When we use read_vector<int>,
// the int will be filled back in and we'll get our old function back.
template<typename T>
std::vector<T> read_vector(std::istream& stream = std::cin) {
    // The function's return type and the type of result need slight changes.
    std::vector<T> result;

    while (true) {
        // We want to copy whatever T is, now, not specifically int.
        std::copy(std::istream_iterator<T>{stream}, std::istream_iterator<T>{},
                std::back_inserter(result));

        // The rest of the function's code doesn't care whether we're working
        // with int or not, so we leave it as it was.

        if (stream.eof())
            break;

        stream.clear();

        std::string s;
        std::getline(stream, s);

        std::cerr << "Warning, ignoring: " << s << "\n";
    }

    return result;
}

/* Above, we said we could pass the template parameters "later".  How much
 * later?  Templates are a compile-time feature of C++.  All types still have to
 * be known when you compile the code, so "later" here means "later in the
 * program text".
 *
 * By the time the program has been compiled, most of the types you could see in
 * the source code are gone.  We will see some ways of working with types at
 * run-time, but those are the exception, not the rule.  Templates are the same
 * way; once your program is compiled, they're gone, and only their
 * instantiations remain.
 */

// We do a similar thing here.
template<typename T>
T sum(std::vector<T> const& v) {
    // We could use 0 as the starting value and assume that 0 can be converted
    // to a T.  However, a better solution is to use T{}, which constructs a T
    // with no parameters.  For int, that's a 0; for double, it's 0.0; for bool,
    // it's false; for std::string, it's the empty string.
    //
    // Note that because of this, sum will work on std::strings!
    return std::accumulate(v.begin(), v.end(), T{});

    // By the way, std::accumulate is itself a template.  We could explicitly
    // specify the template arguments:
    //
    //      std::accumulate<std::vector<T>::const_iterator, T>(
    //          v.begin(), v.end(), T{});
    //
    // Sometimes the compiler is not smart enough to figure it out, so we have
    // to explicitly do this; however, as you can see, it doesn't look
    // particularly good.
}

/* By the way, what if we pass the template a type that doesn't make any sense?
 * For example, what if we try to call sum<void>?  Seeing as templates are done
 * compile-time, the compiler can detect errors like this and give you an error.
 * In this case, it may complain that we're passing void{} to a function, or
 * that std::vector<void> isn't allowed.  These errors are sometimes long and
 * unclear; learning to read them is part of learning C++.
 */

// In the original function, we took int x by value.  However, now that we may
// be dealing with arbitrary T, the copy may be expensive, so we take it by
// const reference.
template<typename T>
std::vector<T> filter_greater_than(std::vector<T> const& v, T const& x) {
    std::vector<T> result;
    // Notice how auto here means we have one less thing to change.
    for (auto e : v)
        if (e > x)
            result.push_back(e);
    return result;
}

template<typename T>
T average(std::vector<T> const& v) {
    if (v.empty())
        return T{};
    // At the moment, we don't enough about the language to be sure T(v.size())
    // is safe.  On the other hand, we also don't know any examples where it's
    // dangerous.  I know this'll be okay, but don't fall into the trap of this
    // being "obviously right"!
    return sum(v)/T(v.size());
}

template<typename T>
bool is_positive(T const& x) {
    return x > T{};
}

template<typename T>
bool all_positive(std::vector<T> const& v) {
    // We can specify template arguments even if we don't immediately call the
    // function and just pass it along.  If we were to not specify it, we'd get
    // an error about the compiler not knowing which one to use.
    return std::all_of(v.begin(), v.end(), is_positive<T>);
}

// Instead of generalising int and taking std::vector<T>::const_iterator, let's
// allow any kind of iterator.  std::copy requires an input iterator to read
// from, so we'll call the type parameter InputIt; this is fairly common.  This
// is purely for people reading our code; the compiler doesn't care what we call
// it.
template<typename InputIt>
void display_range(InputIt begin, InputIt end) {
    std::cout << "{ ";

    // However, we're now faced with a bit of a problem: how do we specify the
    // type that std::ostream_iterator should output?  Had we generalised only
    // over int, that would have been T, but now we need to extract the type of
    // the iterator's value.
    //
    // Fortunately, the designers of the standard library had anticipated this,
    // and so there's a type
    //
    //      std::vector<int>::const_iterator::value_type
    //
    // which is another name for int.  (More generally, if we switch int to T in
    // the above, it'll be another name for T.)  This is not very useful by
    // itself, but if InputIt is another name for
    // std::vector<int>::const_iterator, then we can use InputIt::value_type to
    // get at that type!
    //
    // The above is almost true.  We say that a type is a dependent type when it
    // depends on a template parameter.  InputIt is a template parameter itself,
    // and so is trivially a dependent type.  That means that
    // InputIt::value_type could be either a value or a type.  C++ compilers are
    // only human and have a hard time figuring this out themselves; because of
    // that, we have to write typename before InputIt::value_type to indicate
    // that it is, in fact, a type.
    //
    // For clarity, let's do it in two steps, first making a local name for the
    // type:
    using T = typename InputIt::value_type;

    // Now that we have extracted the value type, we can use it normally as a
    // type.
    std::copy(begin, end, std::ostream_iterator<T>{std::cout, " "});

    std::cout << "}";
}

// We can generalise all the sort-related functions now.  They all use random
// access iterators, so let's call them RandomIt.
template<typename RandomIt>
RandomIt partition(RandomIt begin, RandomIt end);

template<typename RandomIt>
void sort_impl(RandomIt begin, RandomIt end);

/* Didn't we say that declaring templates didn't work?  Not quite.  We can
 * still declare them, but we need to have their definition in the same
 * translation unit.  We just want to write the definitions below the definition
 * of sort.
 */

// Why not make sort work on any container that has begin, end, and random
// access iterators?
template<typename Container>
Container sort(Container v) {

    sort_impl(v.begin(), v.end());
    return v;
}

template<typename RandomIt>
void sort_impl(RandomIt begin, RandomIt end) {
    if (end - begin <= 1)
        return;

    // Notice how usage of auto means we can leave more code unchanged.
    auto pivot = partition(begin, end);
    sort_impl(begin, pivot);
    sort_impl(pivot+1, end);
}

template<typename RandomIt>
RandomIt partition(RandomIt begin, RandomIt end) {
    auto pivot = begin++;

    for (; begin != end; ++begin) {
        if (*pivot > *begin) {
            std::swap(*pivot, *begin);
            ++pivot;
            std::swap(*pivot, *begin);
        }
    }

    return pivot;
}

// I'll leave converting our binary search function into a function template as
// an exercise to the reader.
inline std::vector<int>::const_iterator binary_search(std::vector<int> const& v, int val) {
    auto bottom = v.begin(), top = v.end();

    while (top != bottom) {
        auto mid = bottom + (top - bottom)/2;
        if (*mid < val)
            bottom = mid+1;
        else if (*mid > val)
            top = mid;
        else
            return mid;
    }

    return v.end();
}

/* Now that you've seen how templates are implemented, let's take a look at our
 * main function.
 */

#endif
