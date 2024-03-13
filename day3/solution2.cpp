#include "day3common.hpp"
import fmt;

namespace {
using namespace day3;

const auto get_count = [](const auto &line) {
  std::size_t compartment_index{};
  std::array<std::array<std::size_t, compartment_size>, 3> compartments{};
  std::size_t count{};
  std::string_view lineinput{line.begin(), line.end()};

  for (char index : lineinput) {
    auto char_index = calculate_letter_index(static_cast<unsigned char>(index));

    compartments.at(compartment_index).at(char_index)++;
  }

  fmt::print(" Input {} : {}\n", compartment_index, lineinput);

  if (compartment_index < 2) {
    compartment_index++;
    return std::size_t{};
  }

  for (std::size_t index = 1; index < compartment_size; ++index) {
    if (compartments.at(0).at(index) > 0 && compartments.at(1).at(index) > 0 &&
        compartments.at(2).at(index) > 0) {
      count += index;
      fmt::print("Found character : {} \tWith Count : {} \n\n",
                 calculate_char(index), index);
      break;
    }
  }
  compartment_index = 0;
  compartments[0].fill(0);
  compartments[1].fill(0);
  compartments[2].fill(0);

  return count;
};
} // namespace

int main() {
  try {
    auto lines = std::string_view{inputdata} |
                 std::views::split(line_delimiter) |
                 std::views::transform(get_count) | std::views::common;

    const auto count =
        std::accumulate(lines.begin(), lines.end(), std::size_t{});
    fmt::print("Final Count = {}\n", count);

  } catch (std::exception &e) {
    fmt::print("Error => {}", e.what());
  }
}
