# game_of_life

This is Conway's "Game of Life" in C++ with Intel Threading Building Blocks (TBB).

![run example](https://raw.github.com/cpowell/game_of_life/master/animation.gif)

This source code is inspired by Ruslans' post, "Introduction to high-level multithreading in C++ via Intel TBB library" at http://blog.ruslans.com/2013/08/introduction-to-high-level.html

## Building and testing

This project leverages CMake and Google Test. The following will build the game, build the test binary, and run the tests from the command line:

```
mkdir build && cd build && cmake .. && cmake .. && make && ctest
```

(Yes, run "cmake .." twice. There appears to be a CMake bug or GTest bug that misses the google test configuration the first time.)

The code requires a complier that understands the C++11 standard. Clang/LLVM does this, as does GCC 4.8 or so. Mac OS X Mountain Lion users should be able to build the project either via XCode or the command line with no trouble.

## License

The bundled Intel TBB libraries are distributed under the GNU General Public License version 2, with the so-called “Runtime Exception”. (See http://www.threadingbuildingblocks.org/faq/10 )

All other source code in this repository is licensed under The MIT License; see the LICENSE file for details.


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/cpowell/game_of_life/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

