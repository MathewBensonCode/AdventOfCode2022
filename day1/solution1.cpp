#include "input1.hpp"
#include <algorithm>
#include <ranges>
#include <string_view>
#include <vector>

import day1lib;

int main()
{
  constexpr auto get_section_data = day1::get_section_sum{};
  auto sections = std::string_view{ day1::input_string } | std::views::split(day1::section_delimiter) | std::views::transform(get_section_data);

  std::vector<int> sums{};
  std::ranges::copy(sections, std::back_inserter(sums));
  auto count = *(std::ranges::max_element(sums));

  fmt::print("Highest Element = {}\n ", count);
};
