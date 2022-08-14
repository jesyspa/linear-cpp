# Linear C++

A C++ tutorial that can (hopefully?) be followed without jumping from chapter to chapter at every step.

## Downloads:

- [No project files](https://github.com/jesyspa/linear-cpp/archive/master.zip)
- [Code::Blocks project files](https://github.com/jesyspa/linear-cpp/archive/with_codeblocks_project_files.zip)

## Building

Via a bash shell, compiling all chapters:

```sh
for a in Chapter*; do g++ -std=c++11 -o "$a/out" "$a"/*.cpp; done
```

On OSX:
- You must install XCode and the Command Line Tools package. As of 9/04/2013, Mac OS X doesn't ship with a C++11 compiler.
- Then use clang to build:

```sh
for a in Chapter*; do clang++ --std=c++11 --stdlib=libc++ "$a"/*.cpp -o "$a"/out; done
```

Also, when compiling your own files on either of those two platforms, I recommend you add `-Wall` and `-Wextra` to your flags.  Clang users may also want to add `-fsanitize=undefined`.

## Markdown and EPUB

Thanks to [@Gullumluvl](https://github.com/Gullumluvl) it's
possible to export these chapters as Markdown or epub files!

To do so, just run

```sh
./cpp_2_markdown.py Chapter\ NN*
```

where `NN` is the number of the chapter.

You can use

```sh
./cpp_2_markdown.py .
```

to build the whole book.

For building an epub, make sure you have `pandoc` and run

```sh
pandoc -M author=jesyspa \
  --standalone \
  -V 'header-includes="<style>pre > code.sourceCode {white-space: pre-wrap !important;}</style>"' \
  --toc --toc-depth=1 \
  -o linear-cpp.epub \
  ebook.md
```

The `header-includes` argument is needed to wrap long code lines.

## Future plans

This project is discontinued.  I don't plan to update it for
new C++ standards or add any new language features.

Outline of what's ~~coming~~ missing:
- Practical Examples
- Variants, Optional
- Most of inheritance
- Scope
- Storage Duration
- Undefined Behaviour
- File IO
- Libraries: Boost, Abseil...
- Metaprogramming
- C++14 and up
- The preprocessor
- Most C features

So while I'm glad people have found it useful, please *don't* rely on this by itself to learn C++!
It really only scratches the surface, and you'll do yourself
a service if you get a [good book](https://stackoverflow.com/q/388242/559931).
