#include "input1.hpp"
import std;
import day1lib;

using namespace day1;

int main() {
  try {
    auto sections = input_string | std::views::split(section_delimiter) |
                    std::views::transform(get_section_sum{});

    std::vector<int> results{};
    std::ranges::copy(sections, std::back_inserter(results));

    std::ranges::sort(results, std::ranges::greater());
    auto top3 = results | std::views::take(3) | std::views::common;
    auto highest3 = std::accumulate(top3.begin(), top3.end(), unsigned{});
    std::println("Highest 3 Elements = ");

    for(auto value: top3)
    {
        std::println("{}", value);
    }

    std::println("With sum => {}", highest3);

  } catch (std::exception &caught) {
    std::cerr << "Error: " << caught.what() << "\n";
  }
}
