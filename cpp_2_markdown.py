#!/usr/bin/env python3

"""
Convert a C++ project directory into a markdown book.

Tested on linear-cpp tutorial.

USAGE:

    ./cpp2mkd.py <project directory>

Will create a new file <project directory>_ebook.md


DETAILS:

1. organize folders and files into chapters; if a README is found, it is placed first.
2. put code and inline comments inside fenced code blocks.
3. turn multiline comments into paragraphs;
    * symbols like # _ < > and \\n or \\t are escaped
    * preserve indentation for comments formatted with a leading asterisk:
      - indent > 5 spaces after the asterisk is preserved, thus becoming
        valid markdown indented code block, if preceeded by a blank line;
      - if not preceeded by a blank line, it is turned into inline code;
      - indent > 3 spaces is interpreted as list item; same if line startswith
        an hyphen or asterisk (excluding the comment format asterisk)

Convert to epub with pandoc:

    pandoc -M author=jesyspa --standalone -V 'header-includes="<style>pre > code.sourceCode {white-space: pre-wrap !important;}</style>" --toc --toc-depth=1 -o linear-cpp.epub linear-cpp_ebook.md
    # The header-includes argument is needed to wrap long code lines
"""


import glob
import sys
import os
import os.path as op
import re


START_REGEX = re.compile(r'/\*')
END_REGEX = re.compile(r'\*/')
MKD_ESCAPE = re.compile(r'([#_<>]|(?<!\\)\\[nt])')
TXT_EXTENSIONS = ('.md', '.txt', '.mkd')
CODE_EXTENSIONS = ('.cpp', '.cc', '.h', '.hpp')


def debug(*args, end=None):
    pass


def prepare_mkd_line(line, in_comment_env=None):
    indent = re.search(r'\S|$', line).start()
    if indent < 5:
        line = MKD_ESCAPE.sub(r'\\\1', line)
        if not line.lstrip():
            in_comment_env = None
        elif line.lstrip()[0] in ('*', '-'):
            in_comment_env = 'item'
        elif indent > 3 and in_comment_env != 'item':
            line = '*' + line
            in_comment_env = 'item'
    elif in_comment_env != 'codeblock':
        line = '\n`' + line.strip().replace('`', '\\`') + '`\n'
    else:
        in_comment_env = 'codeblock'

    return line, in_comment_env


def mkd_increment(lines, level=1):
    """Increment titles"""
    for line in lines:
        if line.startswith('#'):
            line = '#'*level + line
            if line.rstrip().endswith('#'):
                line = line.rstrip() + '#'*level + '\n'
        yield line


def code2mkd(lines):
    mkd = ""

    in_comment = 0  # nesting depth of being inside /* ... */ comments.
    star_indent = None  # save the index of the asterisk used to format comments.
    in_comment_env = None  # Inside comments, there can be indented code blocks, and lists

    code = ""      # current code block content. Not written if empty
    
    for lineno, line in enumerate(lines):
        line = line.rstrip()
        column = 0
        debug(lineno, end='. ')
        while True:
            begin = 0
            end = None
            if in_comment:
                debug('in+=', end='')
                match = END_REGEX.search(line)
                indent = 0
                if column == 0 and line.startswith(star_indent):
                    begin = len(star_indent)
                else:
                    # Unindent
                    begin = re.search(r'\S', line).start()
                if match:
                    end = match.start()
                    in_comment -= 1
                debug('%s-%s' % (begin, end), end=' ')
                next_line, in_comment_env = prepare_mkd_line(line[begin:end], in_comment_env)
                mkd += next_line + '\n'  # necessary newline
            else:
                in_comment_env = None
                debug('code', end=' ')
                match = START_REGEX.search(line)
                if match:
                    end = match.start()
                    in_comment += 1
                    star_indent = ' '*end + ' *'
                    if line[:end].rstrip():
                        code += line[:end].rstrip()
                        debug('+=-%s' % (end), end=' ')
                    if code.strip():
                        if mkd:
                            mkd += '\n'
                        mkd += '```cpp\n' + code.lstrip('\n').rstrip() + '\n```\n\n'
                        debug(' >blk.', end=' ')
                        code = ""
                else:
                    code += line.rstrip() + '\n'
                    debug('+=-', end=' ')
                    break
            if match is None:
                break
            line = line[match.end():]
            column += match.end()
        debug('')
    if code.strip():
        debug('Post.', end=' ')
        if mkd:
            mkd += '\n'
        mkd += '```cpp\n' + code.rstrip() + '\n```\n'
    
    return mkd


def codefile2mkd(codefile):
    """Return the markdown text"""
    if codefile == '-':
        return code2mkd(sys.stdin)
    else:
        with open(codefile) as f:
            return code2mkd(f)

def ls(directory):
    content = [name for name in sorted(os.listdir(directory)) if not name.startswith('.')]
    if 'README.md' in content:
        content.remove('README.md')
        content.insert(0, 'README.md')
    return content


def project2mkd(directory):
    """Convert the hierarchy of directories into a hierarchy of chapters"""
    level = 1
    parents = [directory]
    dircontent = {1: ls(directory)}  # at level one
    with open(directory + '_ebook.md', 'w') as out:
        out.write('% ' + directory + '\n%\n%\n\n')
        
        while level:
            try:
                element = dircontent[level].pop(0)
            except IndexError:
                level -= 1
                parents.pop()
                continue

            path = op.join(*parents, element)
            if op.isfile(path):
                out.write('\n' + '#' * level + ' ' + element + '\n\n')
                ext = op.splitext(element)[1]
                if ext in TXT_EXTENSIONS:
                    with open(path) as f:
                        for line in mkd_increment(f):
                            out.write(line)
                elif ext in CODE_EXTENSIONS:
                    out.write(codefile2mkd(path))
            elif op.isdir(path):
                out.write('\n' + '#'*level + ' ' + element + '\n\n')
                level += 1
                parents.append(element)
                if level > 6:
                    print('WARNING: directories deeper than 7 levels are not explored.', file=sys.stderr)
                    out.write('\n- '.join('`%s`' % e for e in ls(path)) + '\n')
                dircontent[level] = ls(path)
            else:
                print('WARNING: Ignored: not a regular file or dir:', element, file=sys.stderr)
    
    

def main():
    try:
        if sys.argv[1] in ('-h', '--help'):
            print(__doc__)
            sys.exit()

        if sys.argv[1] in ('-d', '--debug'):
            global debug
            def debug(*args, end=None): print(*args, end=end, file=sys.stderr)
            directory = sys.argv[2]
        else:
            directory = sys.argv[1]

    except IndexError:
        print(__doc__)
        sys.exit(2)

    project2mkd(directory)


if __name__ == '__main__':
    main()
