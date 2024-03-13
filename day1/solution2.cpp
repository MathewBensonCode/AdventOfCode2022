#include "input1.hpp"
import std;
import fmt;
import day1lib;

using namespace day1;

int main() {
  try {
    std::function<void(std::ranges::range<int>)> get_section_sum_func =
        get_section_sum;

    auto sections = input_string | std::views::split(section_delimiter) |
                    std::views::transform(get_section_sum_func);

    std::vector<int> results{};
    std::ranges::copy(sections, std::back_inserter(results));

    std::ranges::sort(results, std::ranges::greater());
    auto top3 = results | std::views::take(3) | std::views::common;
    auto highest3 = std::accumulate(top3.begin(), top3.end(), 0);
    fmt::print("Highest 3 Elements = {}\n With sum => {}", top3, highest3);

  } catch (std::exception &caught) {
    std::cerr << "Error: " << caught.what() << "\n";
  }
}
