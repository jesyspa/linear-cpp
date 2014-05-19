# Linear C++

A C++ tutorial that can (hopefully?) be followed without jumping from chapter to chapter at every step.

## Downloads:

- [No project files](https://github.com/jesyspa/linear-cpp/archive/master.zip)
- [Code::Blocks project files](https://github.com/jesyspa/linear-cpp/archive/with_codeblocks_project_files.zip)

I'll look into making MinGW Code::Block projects sometimes soon.

## Building

Via a bash shell, compiling all chapters:

```
for a in Chapter*; do g++ -std=c++11 -o "$a/out" "$a"/*.cpp; done
```

On OSX:
- You must install XCode and the Command Line Tools package. As of 9/04/2013, Mac OS X doesn't ship with a C++11 compiler.
- Then use clang to build:

```
for a in Chapter*; do clang++ --std=c++11 --stdlib=libc++ "$a"/*.cpp -o "$a"/out; done
```

Also, when compiling your own files on either of those two platforms, I recommend you add `-Wall` and `-Wextra` to your flags.  Clang users may also want to add `-fsanitize=undefined`.

## Future plans

Outline of what's coming:
- Soon: Enums, More Inheritance, Unions and Variants, Practical Examples
- Unplaced - Casting, Scope, Storage Duration, Undefined Behaviour, Volatile, Metaprogramming, Boost, C++14, File IO, Optional
- Appendices - Declaration Syntax, Pointers to Members, Switch, The Preprocessor

Other plans:
 - Exercises!
 - Generating more human-readable files from the tutorials (or the other way around?)

