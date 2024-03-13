import day1lib;
import std;
import fmt;

using namespace day1;

int main() {
  try {
    std::function<int(const auto&)> get_section_sum_func =
        get_section_sum;

    auto sections = input_string | std::views::split(section_delimiter) |
                    std::views::transform(get_section_sum_func);

    std::vector<int> sums{};
    std::ranges::copy(sections, std::back_inserter(sums));
    const auto count = *(std::ranges::max_element(sums));

    fmt::print("Highest Element = {}\n ", count);

  } catch (std::exception &e) {
    std::cerr << "Error Occurred" << e.what() << '\n';
  }
};
