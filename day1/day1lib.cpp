module;

#include "input1.hpp"

export module day1lib;

import std;

namespace day1
{
export constexpr std::string_view input_string{ inputdata };
export constexpr std::string_view section_delimiter{ "\n\n" };
constexpr std::string_view line_delimiter{ "\n" };

export struct get_section_sum
{
  auto operator()(const auto &section)
  {
    auto lines =
      section | std::views::split(line_delimiter) | std::views::transform([](const auto &line) {
        unsigned number{};
        const auto* line_start = std::ranges::cdata(line);
        std::from_chars(line_start, std::next(line_start, line.size()), number);
        std::print("# {}\n", number);
        return number;
      });

    const auto section_sum = std::accumulate(lines.begin(), lines.end(), unsigned{});
    std::print("Section Sum => {}\n\n", section_sum);
    return section_sum;
  }
};

}// namespace day1
