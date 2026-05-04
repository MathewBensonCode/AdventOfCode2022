#include "input1.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
  std::stringstream inputstream{ inputdata };

    if (!inputstream) {
      return 1;
  }

  std::array<unsigned, 3> highest{};

  auto gethighest = [&](const auto number) {
    std::cout << "\t sum = " << number;
    bool stored = false;
    auto prevhigh{ 0U };

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
      for (const auto high : highest) {
        std::cout << '\t' << high;
      }
  };

  auto sum{ 0U };

    while (!inputstream.eof()) {
      std::string line;
      std::getline(inputstream, line);

      std::cout << "\ninput : " << line;
        if (line.empty()) {
          gethighest(sum);
          sum = 0U;
          printhighest();
          continue;
      }
      auto inputnum = std::stoul(line);
      sum += inputnum;
      std::cout << "\t number : " << inputnum;
    }

  auto totalhighest{ 0U };
    for (const auto high : highest) {
      totalhighest += high;
    }

  std::cout << "\nTotal of 3 highest = " << totalhighest << '\n';
}
