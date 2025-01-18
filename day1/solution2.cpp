import std;
import day1lib;
import input1;

using namespace day1;

namespace
{
constexpr auto get_results()
{
  auto sections = std::string_view{ inputdata } | std::views::split(section_delimiter) | std::views::transform(get_section_sum{}) | std::views::common;
  std::vector<unsigned> results;
  std::ranges::copy(sections, results.begin());
  std::ranges::sort(results, std::ranges::greater());

  return results;
}

}// namespace

int main()
{
    try {
      auto results = get_results();
      auto top3 = results | std::views::take(3) | std::views::common;
      auto highest3 = std::accumulate(top3.begin(), top3.end(), unsigned{});
      std::vector<int> top3results(3);
      std::ranges::copy(top3, std::back_inserter(top3results));
      std::print("Highest 3 Elements = ");

        for (auto value : top3results) {
          std::print("{}\n", value);
        }

      std::print("With sum => {}", highest3);

    } catch (std::exception &caught) {
      std::cerr << "Error: " << caught.what() << "\n";
  }
}
