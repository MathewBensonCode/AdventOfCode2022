module;

#include "input1.hpp"

export module day1lib;

import std;
import fmt;

namespace day1{
export constexpr std::string_view input_string{inputdata};
export constexpr std::string_view section_delimiter{"\n\n"};
export constexpr std::string_view line_delimiter{"\n"};

export const auto get_section_sum{ [](const auto &section) {
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
}
};

} // namespace
