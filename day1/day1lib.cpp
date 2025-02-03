export module day1lib;
import input1;
import std;

namespace day1
{
export constexpr std::string_view input_string{ inputdata };
export constexpr std::string_view section_delimiter{ "\n\n" };
export constexpr std::string_view line_delimiter{ "\n" };

export struct get_section_sum
{

  unsigned constexpr operator()(const auto &section)
  {
    auto lines =
      section | std::views::split(line_delimiter) | std::views::transform([](const auto &line) {
        unsigned number{};
        std::string_view linestring{ line.begin(), line.end() };
        std::from_chars(linestring.data(), (linestring.data() + linestring.size()), number);
        std::print("# {}\n", number);
        return number;
      });

    const auto section_sum = std::reduce(lines.begin(), lines.end(), unsigned{});
    std::print("Section Sum => {}\n\n", section_sum);
    return section_sum;
  }
};

}// namespace day1
