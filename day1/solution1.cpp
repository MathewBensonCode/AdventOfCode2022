#include "input1.hpp"
#include "module1.hpp"
#include <algorithm>
#include <print>

int main()
{
  auto sections = inputdata | std::views::split(std::string_view{"\n\n"}) | std::views::transform(day1::get_section_data);

  std::println("Highest Element = {}\n", std::ranges::max(sections));
}
