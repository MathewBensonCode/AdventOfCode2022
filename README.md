# AdventOfCode2022

These are my C++ Solutions to Advent of Code 2022

## Structure

The input data is stored in a string in the input<day number>.hpp files. Each day has two problems that are stored in folders named part1 and part2. 

The project uses CMake to create the build system.

## How to Run

To run the examples, create a build folder outside the build tree. This will be where the compiled programs will be stored. For example if the code is downloaded and stored in the folder "adventofcode2022source, then the following commands will create the build system using the default Make based generator on linux.

```bash
cd ..
mkdir adventofcode2022build
cmake -B adventofcode2022build -S adventofcode2022source
cd adventofcode2022source
cmake --build ../adventofcode2022build
```

## Code Structure

Each day has 2 parts. Each Day's problems are stored in a folder of the corresponding name. In each folder, solution1 corresponds to the day's first problem and solution2.cpp the second.

The problem of the day is stored in the README.md file stored in the folder.

The input data is copied to a string in the input<daynumber>.hpp file.

If you want to run the programs with your own input data, then you can change the input data in the input<day number>.hpp files.
