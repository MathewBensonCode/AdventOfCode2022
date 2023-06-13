#include "input1.hpp"
#include <algorithm>
#include <charconv>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string_view>
#include <vector>

constexpr std::string_view section_delimiter{"\n\n"};
constexpr std::string_view line_delimiter{"\n"};

const auto get_section_sum = [](const auto &section) {
  auto lines =
      section | std::views::split(line_delimiter) |
      std::views::transform([](const auto &line) {
        std::string_view line_string{line.begin(), line.end()};
        int number{};
        std::from_chars(line_string.data(),
                        line_string.data() + line_string.size(), number);
        fmt::print("# {}\n", number);
        return number;
      });

  const auto section_sum = std::accumulate(lines.begin(), lines.end(), std::size_t{});
  fmt::print("Section Sum => {}\n\n", section_sum);
  return section_sum;
};


int main() {

  auto sections = std::string_view{inputdata} |
                  std::views::split(section_delimiter) |
                  std::views::transform(get_section_sum);

  std::vector<int> results{};
  std::ranges::copy(sections, std::back_inserter(results));

  std::ranges::sort(results, std::ranges::greater());
  auto top3 = results | std::views::take(3) | std::views::common;
  auto highest3 = std::accumulate(top3.begin(), top3.end(), 0);
  fmt::print("Highest 3 Elements = {}\n With sum => {}", top3, highest3);
}
