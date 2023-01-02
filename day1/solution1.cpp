#include "input1.hpp"
#include <array>
#include <iostream>
#include <sstream>

int main() {
  std::stringstream inputstream{inputdata};

  if (!inputstream) {
    return 1;
  }

  std::size_t highest{};
  std::size_t sum{};

  while (!inputstream.eof()) {
    std::string line;
    std::getline(inputstream, line);

    std::cout << "\ninput : " << line;

    if (line.length() == 0) {
      std::cout<<"\t\tSum = "<<sum<<'\n';

      if (sum > highest) {
        highest = sum;
      }
        sum = 0;
        continue;
    }

    auto inputnum = std::stoul(line);
    sum += inputnum;
    std::cout << "\t number : " << inputnum;
  }

  std::cout << "Highest = " << highest << '\n';
}
