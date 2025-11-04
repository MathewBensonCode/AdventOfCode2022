#include "input1.hpp"
#include <algorithm>
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

    if (line.length() == 0) {
      std::cout<<"\t\tSum = "<<sum<<'\n';

      highest = std::max(sum, highest);
        sum = 0;
        continue;
    }

    auto inputnum = std::stoul(line);
    sum += inputnum;
    std::cout << "\t number : " << inputnum << '\n';
  }

  std::cout << "Highest = " << highest << '\n';
}
