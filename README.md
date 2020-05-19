# Calc

An LALR(1) parser implementation of a simple arithmetic expression language. Similar to my [calc-recursive-descent][1] project, but written in C and implemented using [re2c][2] and [LEMON][3].

## Build

To build this project you'll need CMake, a C11 compiler, and [re2c][2]. A copy of the [LEMON][3] utility and its companion parser template are already included in the `vendor` directory. A C++17 compiler is required to perform unit testing.

[1]: https://github.com/JCube001/calc-recursive-descent
[2]: http://re2c.org/
[3]: https://www.hwaci.com/sw/lemon/
