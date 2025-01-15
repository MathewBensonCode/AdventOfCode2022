export module day1lib;
import std;

namespace day1 {
export std::string_view section_delimiter{"\n\n"};
std::string_view line_delimiter{"\n"};

struct string_to_int {
  auto operator()(const auto &line) const{
    int number{};
    std::from_chars(line.begin(), line.end(), number);
    return number;
  }
};

export struct get_section_sum {

  unsigned operator()(const auto &section) {
     auto lines = std::views::transform(
        std::views::split(section, line_delimiter), string_to_int{});

     auto section_sum =
        std::accumulate(lines.begin(), lines.end(), unsigned{});
    return section_sum;
  }
};

} // namespace day1
