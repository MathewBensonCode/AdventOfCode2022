#include "input4.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>

namespace {

using pairs = std::pair<std::size_t, std::size_t>;

const auto print_line = [](const std::string_view &line, const pairs &pair1,
                           const pairs &pair2) {
  std::cout << "\n\nInput : " << line << '\n';

  std::cout << "Pair 1 : " << pair1.first << "-" << pair1.second << '\n';
  std::cout << "Pair 2 : " << pair2.first << "-" << pair2.second << '\n';
};

const auto getpair = [](pairs &pair, std::istream &input) {
  input >> pair.first;
  input.get();
  input >> pair.second;
};

const auto getlinedata = [](const auto &line)->bool {
  std::pair<std::size_t, std::size_t> pair1;
  std::pair<std::size_t, std::size_t> pair2;
  const auto linestring{std::string{line.begin(), line.end()}};
  std::stringstream linestream{linestring};
  getpair(pair1, linestream);
  linestream.get();
  getpair(pair2, linestream);

  print_line(linestring, pair1, pair2);

  return (!((pair1.second < pair2.first) || // pair1 before pair2
            (pair1.first > pair2.second))); // pair1 after pair2
};

constexpr std::string_view line_delimiter{"\n"};

} // namespace

int main() {
  auto lines = inputdata | std::views::split(line_delimiter);
  auto count = std::ranges::count_if(lines, getlinedata);
  std::cout << "Total Found : " << count << '\n';
}
