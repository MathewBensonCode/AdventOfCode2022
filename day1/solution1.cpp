#include "module1.hpp"
#include <algorithm>
#include <print>

int main()
{
  auto sections = day1::get_sections();
  std::println("Highest Element = {}\n", std::ranges::max(sections));
}
