#include "input4.hpp"
#include <algorithm>
#include <charconv>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <iterator>
#include <ranges>

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

const auto getlinedata = [](const auto &linestring) {
  auto pairs = linestring | std::views::split(pair_delimiter) |
               std::views::transform(getpair);

  const auto itr1 = pairs.begin();
  const auto pair1 = *itr1;

  const auto itr2 = std::next(itr1);
  const auto pair2 = *itr2;

  fmt::print("Pair 1 => {} | pair 2 => {} | ", pair1, pair2);

  auto found = (((pair1.first <= pair2.first) &&
                 (pair1.second >= pair2.second)) || // pair2 fits in pair1
                ((pair1.first >= pair2.first) &&
                 (pair1.second <= pair2.second))); // pair1 fits in pair2
  if (found) {
    fmt::print(" FOUND ");
  }
  fmt::print("\n");
  return found;
};

} // namespace

int main() {
  auto lines = inputdata | std::views::split(line_delimiter);
  const auto count{std::ranges::count_if(lines, getlinedata)};
  fmt::print("Total Found : {}\n", count);
} // namespace
