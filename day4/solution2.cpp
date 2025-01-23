import input4;
import std;
import module4;

using namespace day4;

const auto getlinedata = [](const auto &line) {
  auto pairs = line | std::views::split(pair_delimiter) | std::views::transform(getpair{});

  const auto itr1 = pairs.begin();
  const auto pair1 = *itr1;

  const auto itr2 = std::next(itr1);
  const auto pair2 = *itr2;

  std::print("Pair 1 => {} | Pair 2 => {} ", pair1, pair2);

  const bool found = (!((pair1.second < pair2.first) ||// pair1 before pair2
                        (pair1.first > pair2.second)));// pair1 after pair2
    if (found) {
      std::print("| Found");
  }
  std::print("\n");
  return found;
};

int main()
{
    try {
      auto lines =
        std::string_view{ inputdata } | std::views::split(line_delimiter);
      auto count = std::ranges::count_if(lines, getlinedata);
      std::print("Total Found : {} \n", count);
    } catch (std::exception &e) {
      std::cerr << std::format("Exception : {}\n", e.what());
  }
}
