#include "input4.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>

namespace {


const auto getpair = [](std::istream &input) {
  std::size_t first{};
  input >> first;
  input.get();
  std::size_t second{};
  input >> second;
  return std::make_pair(first, second);
};

const auto getlinedata = [](const auto &line){
  std::stringstream linestream{std::string{line.begin(), line.end()}};
  const auto pair1 = getpair(linestream);
  linestream.get();
  const auto pair2 = getpair(linestream);

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
