#include "input6.hpp"
#include <iostream>
#include <map>
#include <ranges>
#include <string_view>
#include <vector>

int main() {

  const auto width{4};

  for (auto index{0UL}; index < inputdata.length() - 4; ++index) {

    auto endlocation = width + index;
    auto vals = std::ranges::views::all(inputdata) |
                std::ranges::views::drop(index) |
                std::ranges::views::take(width);

    const std::string_view store(std::begin(vals), std::end(vals));

    std::cout << store << '\t' << endlocation << '\n';

    auto not_unique{0UL};

    for (const auto &val : store) {
      if (store.find(val) != store.rfind(val)) {
        not_unique++;
      }
    }

    if (not_unique == 0) {
      std::cout << "\t\tFound It\n";
      break;
    }
  }
}
