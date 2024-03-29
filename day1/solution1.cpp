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
                       std::string_view line_string{line.begin(), line.end()};
                       std::from_chars(line_string.data(), line_string.data()+line_string.size(), number);
                       return number;
               });

  return std::accumulate(lines.begin(), lines.end(), 0);
};

} // namespace

int main() {
  auto sections = inputdata | std::views::split(section_delimiter) |
                  std::views::transform(get_section_data);

  auto count = *(std::ranges::max_element(sections));

  std::cout << "Highest Element = " << count <<'\n';
}
