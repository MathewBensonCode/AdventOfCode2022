#include "input1.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>

import day1lib;

int main() {
  try {
    auto sections = std::views::split(day1::section_delimiter) |
                    std::views::transform(day1::get_section_sum{});

    std::vector<int> results{};
    std::ranges::copy(day1::input_string | sections,
                      std::back_inserter(results));

    std::ranges::sort(results, std::ranges::greater());
    auto top3 = results | std::views::take(3) | std::views::common;
    auto highest3 = std::accumulate(top3.begin(), top3.end(), 0);
    std::vector<int> top3results(3);
    std::ranges::copy(top3, std::back_inserter(top3results));
    fmt::print("Highest 3 Elements = ");

    for (auto value : top3results) {
      fmt::print("{}\n", value);
    }

    fmt::print("With sum => {}", highest3);

  } catch (std::exception &caught) {
    std::cerr << "Error: " << caught.what() << "\n";
  }
}
