#include "input1.hpp"
#include <algorithm>
#include <charconv>
#include <numeric>
#include <vector>

int main() {
  std::vector<unsigned> sums{};
  std::vector<unsigned> nums{};

    for (auto start_iterator{ std::begin(inputdata)}, end_iterator {std::end(inputdata)} ; start_iterator != end_iterator; std::ranges::advance(start_iterator, 1, end_iterator)) {

      const auto *endline = std::ranges::find(start_iterator, end_iterator, '\n');
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

}
