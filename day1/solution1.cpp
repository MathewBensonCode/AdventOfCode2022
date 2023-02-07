#include "input1.hpp"
#include <algorithm>
#include <charconv>
#include <fmt/core.h>
#include <numeric>
#include <ranges>
#include <string_view>
#include <vector>

namespace {
constexpr std::string_view section_delimiter{"\n\n"};
constexpr std::string_view line_delimiter{"\n"};

const auto get_section_data = [](const auto &section) {
  auto lines =
      section | std::views::split(line_delimiter) |
      std::views::transform([](const auto &line) {
        int number{};
        std::string_view line_string{line.begin(), line.end()};
        std::from_chars(line_string.data(),
                        line_string.data() + line_string.size(), number);
        fmt::print("# {}\n", number);
        return number;
      });

  const auto section_sum = std::accumulate(lines.begin(), lines.end(), 0);
  fmt::print("Section Sum => {}\n\n", section_sum);
  return section_sum;
};

} // namespace

int main() {
  auto sections = std::string_view{inputdata} |
                  std::views::split(section_delimiter) |
                  std::views::transform(get_section_data);

  std::vector<int> sums{};
  std::ranges::copy(sections, std::back_inserter(sums));
  auto count = *(std::ranges::max_element(sums));

  fmt::print("Highest Element = {}\n ", count);
};
