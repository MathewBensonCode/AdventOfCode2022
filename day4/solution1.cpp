import input4;
import std;
import module4;

using namespace std::literals::string_view_literals;
using namespace day4;

const auto getlinedata = [](const auto &linestring) {
  auto pairs = linestring | std::views::split(pair_delimiter) | std::views::transform(getpair{});

  const auto itr1 = pairs.begin();
  const auto pair1 = *itr1;

  const auto itr2 = std::next(itr1);
  const auto pair2 = *itr2;

  std::print("Pair 1 => {} | pair 2 => {} | ", pair1, pair2);

  auto found = (((pair1.first <= pair2.first) && (pair1.second >= pair2.second)) ||// pair2 fits in pair1
                ((pair1.first >= pair2.first) && (pair1.second <= pair2.second)));// pair1 fits in pair2
    if (found) {
      std::print(" FOUND ");
  }
  std::print("\n");
  return found;
};

int main()
{
    try {
      auto lines =
        std::string_view{ inputdata } | std::views::split(line_delimiter);
      const auto count{ std::ranges::count_if(lines, getlinedata) };
      std::print("Total Found : {}\n", count);
    } catch (std::exception &e) {
      std::cerr << std::format("Exception : {}\n", e.what());
  }
}// namespace
