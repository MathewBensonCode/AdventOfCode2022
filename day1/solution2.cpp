import std;
import day1lib;
import input1;

using namespace day1;

int main()
{
    try {
      auto sections = std::string_view{ inputdata } | std::views::split(std::string_view{"\n\n"}) | std::views::transform(get_section_sum{});
      std::vector<unsigned> results{};
      std::ranges::copy(sections, std::back_inserter(results));
      std::ranges::sort(results, std::ranges::greater());
      auto top3 = results | std::views::take(3) | std::views::common;
      auto highest3 = std::reduce(top3.begin(), top3.end(), unsigned{});
      std::println("Highest 3 Elements = {}\n With sum => {}", top3, highest3);
    } catch (std::exception &caught) {
      std::cerr << "Error: " << caught.what() << "\n";
  }
}
