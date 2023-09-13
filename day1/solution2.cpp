import day1lib;
import std;
import fmt;

int main() {

  using namespace day1;

  auto sections = input_string |
                  std::views::split(section_delimiter) |
                  std::views::transform(get_section_sum);

  std::vector<int> results{};
  std::ranges::copy(sections, std::back_inserter(results));

  std::ranges::sort(results, std::ranges::greater());
  auto top3 = results | std::views::take(3) | std::views::common;
  auto highest3 = std::accumulate(top3.begin(), top3.end(), 0);
  fmt::print("Highest 3 Elements = {}\n With sum => {}", top3, highest3);
}
