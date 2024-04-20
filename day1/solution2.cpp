#include "input1.hpp"
import std;
import day1lib;

using namespace day1;

int main() {
  try {
    auto sections = input_string | std::views::split(section_delimiter) |
                    std::views::transform(get_section_sum);

    std::vector<int> results{};
    std::ranges::copy(sections, std::back_inserter(results));

    std::ranges::sort(results, std::ranges::greater());
    auto top3 = results | std::views::take(3) | std::views::common;
    auto highest3 = std::accumulate(top3.begin(), top3.end(), 0);
    std::vector<int> top3results(3);
    std::ranges::copy(top3, std::back_inserter(top3results));
    std::print("Highest 3 Elements = ");

    for(auto value: top3results)
    {
        std::print("{}\n", value);
    }

    std::print("With sum => {}", highest3);

  } catch (std::exception &caught) {
    std::cerr << "Error: " << caught.what() << "\n";
  }
}
