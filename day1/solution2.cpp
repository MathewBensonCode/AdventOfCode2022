#include "input1.hpp"
#include <iostream>
#include <numeric>
#include <ranges>
#include <string_view>
#include <functional>
#include <algorithm>

int main() {

  constexpr std::string_view inputstringview{inputdata};
  constexpr std::string_view section_delimiter{"\n\n"};
  constexpr std::string_view line_delimiter{"\n"};

  auto sections =
      inputstringview | std::views::split(section_delimiter) |
      std::views::transform([&line_delimiter](const auto &section) {
        auto lines =
            section | std::views::split(line_delimiter) |
            std::views::transform([](const auto &line) {
              return std::string(line.begin(), line.end());
            }) |
            std::views::transform([](const auto &linestring) {
              return linestring.length() > 0 ? std::stoi(linestring) : 0;
            });

        return std::accumulate(lines.begin(), lines.end(), 0);
      });

  std::vector<int> results;
  std::ranges::copy(sections, std::back_inserter(results));

  std::ranges::sort(results, std::ranges::greater());
  auto top3 = results | std::views::take(3) | std::views::common;
  auto highest3 = std::accumulate(top3.begin(), top3.end(), 0);
  std::cout << "Sum of Hightest 3 Elements = " << highest3<<'\n';
}
