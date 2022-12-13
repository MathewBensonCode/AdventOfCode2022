#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  std::ifstream inputfile{"input"};

  if (!inputfile) {
    std::cerr << "Input File Not Found\n";
    return 1;
  }

  std::size_t count{};
  std::pair<std::size_t, std::size_t> pair1;
  std::pair<std::size_t, std::size_t> pair2;

  auto getpair = [](std::pair<std::size_t, std::size_t> &pair,
                    std::istream &input) {
    char delimiter{};
    input >> pair.first;
    input.get(delimiter);
    if (delimiter == '-') {
      input >> pair.second;
    }
  };

  auto getlinedata = [&](std::string linestring) {
    char delimiter;
    std::stringstream linestream{linestring};
    getpair(pair1, linestream);
    linestream.get(delimiter);
    if (delimiter == ',') {
      getpair(pair2, linestream);
    }
  };

  while (!inputfile.eof()) {
    std::string linestring{};
    std::getline(inputfile, linestring);

    if (linestring.length() == 0) {
      continue;
    }

    getlinedata(linestring);

    if (!((pair1.second < pair2.first) ||  // pair1 before pair2
          (pair1.first > pair2.second))) { // pair1 after pair2
      count++;
      std::cout << "\nInput : " << linestring << '\n';

      std::cout << "Pair 1 : " << pair1.first << "-" << pair1.second << '\n';
      std::cout << "Pair 2 : " << pair2.first << "-" << pair2.second << '\n';
    }
  }
  std::cout << "Total Found : " << count << '\n';
}
