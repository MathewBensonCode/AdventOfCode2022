#include "input4.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <charconv>

namespace {

constexpr auto line_delimiter{"\n"sv};
constexpr auto pair_delimiter{","sv};
constexpr auto num_delimiter{"-"sv};

const auto getpair = [](const auto &pair) {
  auto numbers = pair | std::views::split(num_delimiter) |
                 std::views::transform([](const auto &num) {
                   int number{};
                   std::from_chars(num.begin(), num.end(), number);
                   return number;
                 });

  const auto first = std::ranges::begin(numbers);
  const auto second = std::next(first);

  return std::make_pair(*first, *second);
};

const auto getlinedata = [](const auto &line){
  auto pairs = line | std::views::split(pair_delimiter) |
               std::views::transform(getpair);

  const auto itr1 = pairs.begin();
  const auto pair1 = *itr1;

  const auto itr2 = std::next(itr1);
  const auto pair2 = *itr2;

  return (!((pair1.second < pair2.first) || // pair1 before pair2
            (pair1.first > pair2.second))); // pair1 after pair2
};

} // namespace

int main() {
  auto lines = inputdata | std::views::split(line_delimiter);
  auto count = std::ranges::count_if(lines, getlinedata);
  std::cout << "Total Found : " << count << '\n';
}
