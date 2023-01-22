# AdventOfCode2022

[![CMake-Windows-MSVC](https://github.com/MathewBensonCode/AdventOfCode2022/actions/workflows/windows_cmake.yml/badge.svg)](https://github.com/MathewBensonCode/AdventOfCode2022/actions/workflows/windows_cmake.yml)

[![CMake-Linux-GCC](https://github.com/MathewBensonCode/AdventOfCode2022/actions/workflows/cmake.yml/badge.svg)](https://github.com/MathewBensonCode/AdventOfCode2022/actions/workflows/cmake.yml)

These are my C++ Solutions to Advent of Code 2022

## Code Structure

Each day has 2 parts. Each Day's problems are stored in a folder of the corresponding name. In each folder, solution1 corresponds to the day's first problem and solution2.cpp the second.

The problem of the day is stored in the README.md file stored in the folder.

The input data is copied to a string in the input<daynumber>.hpp file.

If you want to run the programs with your own input data, then you can change the input data in the input<day number>.hpp files.

The CMake Build has extracts from [lefticus/gui_starter_template](https://github.com/cpp-best-practices/gui_starter_template). The main extracts are the compiler warning levels that ensure better c++ code.

The build process is designed to work with neovim and the clangd lsp. The generated compile_commands.json which is created in the build folder using cmake, is linked into the source root directory so that the compile commands for the source files are available to the lsp tools. 


## How to Run

To run the examples, create a build folder outside the build tree. This will be where the compiled programs will be stored. For example if the code is downloaded and stored in the folder "adventofcode2022source, then the following commands will create the build system using the default Make based generator on linux.

```bash
cd ..
mkdir adventofcode2022build
cmake -B adventofcode2022build -S adventofcode2022source
cd adventofcode2022source
cmake --build ../adventofcode2022build
```

## Required Libraries

The fmt library is required to be installed on your operating system of choice. For windows this can be done via vcpkg and on other operating systems like linux it can be installed via the package manager. 
