module;

#include "input1.hpp"
#include <charconv>
#include <numeric>
#include <ranges>
#include <string_view>

export module day1lib;

export import fmt;

namespace day1
{
export constexpr std::string_view input_string{ inputdata };
export constexpr std::string_view section_delimiter{ "\n\n" };
constexpr std::string_view line_delimiter{ "\n" };

export struct get_section_sum
{

  get_section_sum() = default;
  get_section_sum &operator=(const get_section_sum &) = delete;
  get_section_sum &operator=(get_section_sum &&) = delete;
  get_section_sum(const get_section_sum &) = default;
  get_section_sum(get_section_sum &&) = default;
  ~get_section_sum() = default;

  auto operator()(const auto &section)
  {
    auto lines =
      section | std::views::split(line_delimiter) | std::views::transform([](const auto &line) {
        int number{};
        std::string_view line_string{ line.begin(), line.end() };
        std::from_chars(line_string.data(),
          line_string.data() + line_string.size(),
          number);
        fmt::print("# {}\n", number);
        return number;
      });

    const auto section_sum = std::accumulate(lines.begin(), lines.end(), 0);
    fmt::print("Section Sum => {}\n\n", section_sum);
    return section_sum;
  }
};

}// namespace day1
