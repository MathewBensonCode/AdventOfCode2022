#include "input1.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

namespace {
constexpr std::string_view section_delimiter{"\n\n"};
constexpr std::string_view line_delimiter{"\n"};

const auto get_section_data = [](const auto &section) {
  auto lines = section | std::views::split(line_delimiter) |
               std::views::transform([](const auto &line) {
                 return std::string(line.begin(), line.end());
               }) |
               std::views::transform([](const auto &linestring) {
                 return linestring.length() > 0 ? std::stoi(linestring) : 0;
               });
  return std::accumulate(lines.begin(), lines.end(), 0);
};

} // namespace

int main() {

  auto sections = inputdata | std::views::split(section_delimiter) |
                  std::views::transform(get_section_data);

  std::vector<int> results{};
  std::ranges::copy(sections, std::back_inserter(results));

  std::ranges::sort(results, std::ranges::greater());
  auto top3 = results | std::views::take(3) | std::views::common;
  auto highest3 = std::accumulate(top3.begin(), top3.end(), 0);
  std::cout << "Sum of Hightest 3 Elements = " << highest3 << '\n';
}
