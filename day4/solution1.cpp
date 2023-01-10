#include "input4.hpp"
#include <iostream>
#include <sstream>

namespace {
using pairs = std::pair<std::size_t, std::size_t>;

const auto getpair = [](pairs &pair, std::istream &input) {
  char delimiter{};
  input >> pair.first;
  input.get(delimiter);
  if (delimiter == '-') {
    input >> pair.second;
  }
};

const auto getlinedata = [](const std::string &linestring, pairs &pair1,
                            pairs &pair2) {
  char delimiter{};
  std::istringstream linestream{linestring};
  getpair(pair1, linestream);
  linestream.get(delimiter);
  if (delimiter == ',') {
    getpair(pair2, linestream);
  }
};
} // namespace

int main() {

  std::istringstream inputstringstream{std::string{inputdata}};

  std::size_t count{};
  std::pair<std::size_t, std::size_t> pair1;
  std::pair<std::size_t, std::size_t> pair2;

  while(!inputstringstream.eof()){
    std::string line;
    std::getline(inputstringstream, line);

    getlinedata(line, pair1, pair2);

    std::cout << "\nInput : " << line << '\n';

    std::cout << "Pair 1 : " << pair1.first << "-" << pair1.second << '\n';
    std::cout << "Pair 2 : " << pair2.first << "-" << pair2.second << '\n';

    if (((pair1.first <= pair2.first) &&
         (pair1.second >= pair2.second)) || // pair2 fits in pair1
        ((pair1.first >= pair2.first) &&
         (pair1.second <= pair2.second))) { // pair1 fits in pair2
      std::cout << " Found Match \n";
      count++;
    }
  }

  std::cout << "Total Found : " << count << '\n';
}
