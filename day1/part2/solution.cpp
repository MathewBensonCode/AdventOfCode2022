#include "input1.hpp"
#include <array>
#include <iostream>
#include <sstream>

int main() {
  std::stringstream inputstream{inputdata};

  if (!inputstream) {
    return 1;
  }

  std::array<std::size_t, 3> highest{};

  auto gethighest = [&](const std::size_t number) {
    std::cout << "\t sum = " << number;
    bool stored = false;
    std::size_t prevhigh{};

    for (auto &high : highest) {
      if (high == 0) {
        high = number;
        break;
      }

      if (number > high && !stored) {
        prevhigh = high;
        high = number;
        stored = true;
      }
      if (prevhigh > high && stored) {
        auto temp = high;
        high = prevhigh;
        prevhigh = temp;
      }
    }
  };

  auto printhighest = [&]() {
    std::cout << "\nHighest => :\n";
    for (auto high : highest) {
      std::cout << '\t' << high;
    }
  };

  std::size_t sum{};

  while (!inputstream.eof()) {
    std::string line;
    std::getline(inputstream, line);

    std::cout << "\ninput : " << line;
    if (line.length() == 0) {
      gethighest(sum);
      sum = 0;
      printhighest();
      continue;
    }
    auto inputnum = std::stoul(line);
    sum += inputnum;
    std::cout << "\t number : " << inputnum;
  }

  std::size_t totalhighest{0};
  for (auto high : highest) {
    totalhighest += high;
  }

  std::cout << "\nTotal of 3 highest = " << totalhighest << '\n';
}
