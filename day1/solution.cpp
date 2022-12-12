#include <array>
#include <fstream>
#include <iostream>

int main() {
  std::ifstream file{"input.txt"};
  if (!file)
    return 1;

  std::array<unsigned int, 3> highest{};

  auto gethighest = [&](const unsigned int number) {
    std::cout << "\t sum = " << number;
    bool stored = false;
    unsigned int prevhigh{};

    for (auto &high : highest) {
      if (high == 0) {
        high = number;
        break;
      }

      if (number > high && stored == false) {
        prevhigh = high;
        high = number;
        stored = true;
      }
      if (prevhigh > high && stored == true) {
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

  unsigned int sum{};

  while (!file.eof()) {
    std::string line;
    std::getline(file, line);

    std::cout << "\ninput : " << line;
    if (line.length() == 0) {
      gethighest(sum);
      sum = 0;
      printhighest();
      continue;
    }
    unsigned int inputnum = std::stoi(line);
    sum += inputnum;
    std::cout << "\t number : " << inputnum;
  }

  std::cout << "\n\nTop 3" << '\n';

  auto totalhighest{0};
  for (auto high : highest) {
    totalhighest += high;
  }

  printhighest();

  std::cout << "Total 3 highest = " << totalhighest << '\n';
}
