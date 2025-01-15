import day1lib;
import std;
import input1;

using namespace day1;

auto get_highest() {

  auto sections = std::string_view{inputdata} |
                  std::views::split(section_delimiter) |
                  std::views::transform(get_section_sum{});

  return *(std::ranges::max_element(sections));
};

int main() {

  try {

    auto highest = get_highest();

    std::print("Highest Element = {}\n ", highest);

  } catch (std::exception &e) {
    std::cerr << "Error Occurred" << e.what() << '\n';
  }
}
