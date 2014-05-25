#include "symbol_table.hpp"
#include "builtin_operations.hpp"

SymbolTable get_default_symbol_table() {
    return {
        {"+", builtin_add},
        {"-", builtin_subtract},
        {"*", builtin_multiply},
        {"/", builtin_divide}
    };
}
