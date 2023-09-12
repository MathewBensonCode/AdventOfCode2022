#include "header1.hpp"
#include "input1.hpp"
#include <algorithm>
#include <vector>
import fmt;

using namespace day1;

int main() {
  auto sections = std::string_view{inputdata} |
                  std::views::split(section_delimiter) |
                  std::views::transform(get_section_sum);

  std::vector<int> sums{};
  std::ranges::copy(sections, std::back_inserter(sums));
  const auto count = *(std::ranges::max_element(sums));

  fmt::print("Highest Element = {}\n ", count);
};
