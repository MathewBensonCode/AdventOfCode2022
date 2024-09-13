module;

#include "input1.hpp"

export module day1lib;
import std;

namespace day1 {
export constexpr std::string_view input_string{inputdata};
export constexpr std::string_view section_delimiter{"\n\n"};
export constexpr std::string_view line_delimiter{"\n"};

export struct get_section_sum {

  unsigned constexpr operator()(const auto &section) {
    auto lines =
        section | std::views::split(line_delimiter) |
        std::views::transform([](const auto &line) {
          int number{};
          std::string_view line_string{line.begin(), line.end()};
          std::from_chars(line_string.data(),
                          line_string.data() + line_string.size(), number);
          std::print("# {}\n", number);
          return number;
        });

  const auto section_sum = std::accumulate(lines.begin(), lines.end(), unsigned{});
  std::print("Section Sum => {}\n\n", section_sum);
  return section_sum;
  }
};

} // namespace day1
