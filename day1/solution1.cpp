#include "input1.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <charconv>

namespace {
constexpr std::string_view section_delimiter{"\n\n"};
constexpr std::string_view line_delimiter{"\n"};

const auto get_section_data = [](const auto &section) {
  auto lines = section | std::views::split(line_delimiter) |
               std::views::transform([](const auto &line) {
                  int number{};
                  std::from_chars(line.begin(), line.end(), number);
                  return number;
               });

  return std::accumulate(lines.begin(), lines.end(), 0);
};

} // namespace

int main() {
  auto sections = inputdata | std::views::split(section_delimiter) |
                  std::views::transform(get_section_data);

  std::cout << "Hightest Element = " << *(std::ranges::max_element(sections));
}
