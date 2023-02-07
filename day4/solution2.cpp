#include "input4.hpp"
#include <algorithm>
#include <charconv>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <ranges>
#include <string_view>

using namespace std::literals::string_view_literals;

namespace {

constexpr auto line_delimiter{"\n"sv};
constexpr auto pair_delimiter{","sv};
constexpr auto num_delimiter{"-"sv};

const auto getpair = [](const auto &pair) {
  auto numbers =
      pair | std::views::split(num_delimiter) |
      std::views::transform([](const auto &num) {
        std::string_view num_string{num.begin(), num.end()};
        int number{};
        std::from_chars(num_string.data(),
                        num_string.data() + num_string.size(), number);
        return number;
      });

  const auto first = std::ranges::begin(numbers);
  const auto second = std::next(first);

  return std::make_pair(*first, *second);
};

const auto getlinedata = [](const auto &line) {
  auto pairs =
      line | std::views::split(pair_delimiter) | std::views::transform(getpair);

  const auto itr1 = pairs.begin();
  const auto pair1 = *itr1;

  const auto itr2 = std::next(itr1);
  const auto pair2 = *itr2;

  fmt::print("Pair 1 => {} | Pair 2 => {} ", pair1, pair2);

  const bool found = (!((pair1.second < pair2.first) || // pair1 before pair2
                        (pair1.first > pair2.second))); // pair1 after pair2
  if (found) {
    fmt::print("| Found");
  }
  fmt::print("\n");
  return found;
};

} // namespace

int main() {
  auto lines = std::string_view{inputdata} | std::views::split(line_delimiter);
  auto count = std::ranges::count_if(lines, getlinedata);
  fmt::print("Total Found : {} \n", count);
}
