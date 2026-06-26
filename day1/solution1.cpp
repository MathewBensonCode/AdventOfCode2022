#include "input1.hpp"
#include <algorithm>
#include <iterator>
#include <print>
#include <string_view>
#include <numeric>
#include <vector>
#include <string>

int main()
{
  std::string_view inputdata(inputstring);
  std::vector<unsigned> sums{};

    for (auto start_iterator{ std::begin(inputdata) },
      end_iterator{ std::end(inputdata) };
      start_iterator != end_iterator;
      std::advance(start_iterator, 1)) {

      std::vector<unsigned> nums{};

      auto endline = std::find(start_iterator, end_iterator, '\n');

      std::string number_string{ start_iterator, endline };

      unsigned number = static_cast<unsigned>(stoul(number_string));

        if (number > 0) {
          start_iterator = endline;
          nums.push_back(number);
          continue;
      }

      const auto sum = std::accumulate(nums.begin(), nums.end(), unsigned{});
      sums.push_back(sum);
      start_iterator = endline;
    }

  std::println("Highest Section Sum = > {}", *(std::max_element(std::begin(sums), std::end(sums))));
}
