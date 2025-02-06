export module day1lib;
import std;

namespace day1
{

struct string_to_int
{
  auto operator()(const auto &line) const
  {
    unsigned number{};
    std::string_view line_string{line.begin(), line.end()};
    std::from_chars(line_string.data(), line_string.data()+line_string.size(), number);
    std::println("{}", number);
    return number;
  }
};

export struct get_section_sum
{

  unsigned operator()(const auto &section)
  {
    std::string_view line_delimiter{ "\n" };
    auto lines = std::views::transform(
      std::views::split(section, line_delimiter), string_to_int{});

    auto section_sum =
      std::accumulate(lines.begin(), lines.end(), unsigned{});
    std::println("Section Sum => {}\n", section_sum);
    return section_sum;
  }
};

}// namespace day1
