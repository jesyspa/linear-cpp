#ifndef CHAPTER_20_SYMBOL_TABLE_HPP
#define CHAPTER_20_SYMBOL_TABLE_HPP

#include <functional>
#include <map>
#include <string>
#include <vector>

using Operation = std::function<int(std::vector<int> const&)>;
using SymbolTable = std::map<std::string, Operation>;

SymbolTable get_default_symbol_table();

#endif
