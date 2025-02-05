import std;
import day1lib;

using namespace day1;

int main()
{
    try {
      auto sections = input_string | std::views::split(section_delimiter) | std::views::transform(get_section_sum{});

      std::vector<unsigned> results{};
      std::ranges::copy(sections, std::back_inserter(results));

    std::ranges::sort(results, std::ranges::greater());
    auto top3 = results | std::views::take(3) | std::views::common;
    const auto highest3 = std::accumulate(top3.begin(), top3.end(), 0);
    std::array<int,3> top3results{};
    std::ranges::copy(top3, top3results.begin());

      std::println("Highest 3 Sections => {} \nWith sum => {}", top3results, highest3);

  } catch (std::exception &caught) {
    std::cerr << "Error: " << caught.what() << "\n";
  }
}
