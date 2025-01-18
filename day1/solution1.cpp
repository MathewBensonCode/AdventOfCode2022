import day1lib;
import std;
import input1;

using namespace day1;

namespace
{

consteval auto get_highest()
{
  constexpr std::string_view all_data{ inputdata };
  std::vector<unsigned> sums{};
  std::vector<unsigned> nums{};

    for (const auto *start_iterator{ all_data.begin() }; start_iterator != all_data.end(); std::ranges::advance(start_iterator, 1, all_data.end())) {

      const auto *endline = std::ranges::find(start_iterator, all_data.end(), '\n');
      unsigned number{};
      std::from_chars(start_iterator, endline, number);

        if (number > 0) {
          start_iterator = endline;
          nums.push_back(number);
          continue;
      }

      const auto sum = std::reduce(nums.begin(), nums.end(), unsigned{});
      nums.clear();
      sums.push_back(sum);
      start_iterator = endline;
    }

  return std::ranges::max(sums);
};
}// namespace

int main()
{

    try {

      auto highest = get_highest();

      std::print("Highest Element = {}\n ", highest);

    } catch (std::exception &e) {
      std::cerr << "Error Occurred" << e.what() << '\n';
  }
}
