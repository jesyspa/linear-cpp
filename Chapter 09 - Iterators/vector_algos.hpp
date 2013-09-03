#ifndef CHAPTER_09_VECTOR_ALGOS_HPP
#define CHAPTER_09_VECTOR_ALGOS_HPP

#include <vector>

std::vector<int> read_int_vector();

// Well, what do you know, we were right about both!
std::vector<int> sort(std::vector<int> v);
bool binary_search(std::vector<int> v, int val);

// I suppose it isn't entirely fair, as I was the one to choose them...

// There's nothing surprising or new in this header; let's go on to
// vector_algos.cpp

#endif
