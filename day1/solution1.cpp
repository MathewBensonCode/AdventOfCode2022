import day1lib;
import std;
import input1;

using namespace day1;
int main()
{
    try {
      auto sections = std::string_view{ inputdata } | std::views::split(std::string_view{"\n\n"}) | std::views::transform(get_section_sum{});
      std::print("Highest Element = {}\n ", std::ranges::max(sections));
    } catch (std::exception &e) {
      std::cerr << "Error Occurred" << e.what() << '\n';
  }
}
