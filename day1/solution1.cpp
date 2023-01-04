#include "input1.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string_view>

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

  std::cout << "Hightest Element = " << *(std::ranges::max_element(sections));
}
