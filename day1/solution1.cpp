import day1lib;
import std;

using namespace day1;

int main() {
  try {
    auto sections = input_string | std::views::split(section_delimiter) |
                    std::views::transform(get_section_sum);

    std::vector<int> sums{};
    std::ranges::copy(sections, std::back_inserter(sums));
    const auto count = *(std::ranges::max_element(sums));

    std::print("Highest Element = {}\n ", count);

  } catch (std::exception &e) {
    std::cerr << "Error Occurred" << e.what() << '\n';
  }
};
