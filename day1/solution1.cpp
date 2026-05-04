#include "input1.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::stringstream inputstream{inputdata};

  if (!inputstream) {
    return 1;
  }

  auto highest{0U};
  auto sum{0U};

  while (!inputstream.eof()) {
    std::string line;
    std::getline(inputstream, line);

    if (line.empty()) {
      std::cout<<"\t\tSum = "<<sum<<'\n';

      highest = std::max(sum, highest);
        sum = 0U;
        continue;
    }

    const auto inputnum = std::stoul(line);
    sum += inputnum;
    std::cout << "\t number : " << inputnum << '\n';
  }

  std::cout << "Highest = " << highest << '\n';
}
