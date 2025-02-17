#include <numeric>
#include <ranges>
#include <charconv>

#include "input1.hpp"

namespace day1
{
inline constexpr std::string_view section_delimiter{ "\n\n" };
constexpr std::string_view line_delimiter{ "\n" };

const auto get_section_data = [](const auto &section) {
  auto lines = section | std::views::split(line_delimiter) | std::views::transform([](const auto &line) {
    int number{};
    std::string_view line_string{ line.begin(), line.end() };
    std::from_chars(line_string.data(), line_string.data() + line_string.size(), number);
    return number;
  });

  return std::accumulate(lines.begin(), lines.end(), 0);
};

inline auto get_sections()
{
  return inputdata | std::views::split(std::string_view{ "\n\n" }) | std::views::transform(day1::get_section_data);
}

}// namespace day1
