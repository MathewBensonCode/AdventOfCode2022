#include "input3.hpp"
#include <array>
#include <ranges>
#include <string_view>
#include <numeric>
#include <fmt/format.h>

namespace {
const auto compartment_size{53};
const auto small_letter_offset{96};
const auto capital_letter_offset{38};
const auto small_capital_boundary{27};

constexpr std::string_view line_delimiter{"\n"};

const auto calculate_index = [](unsigned char letter) {
  auto value = static_cast<unsigned long>(letter);

  if (value > small_letter_offset) {
    return value - small_letter_offset;
  }
  return value - capital_letter_offset;
};

const auto calculate_char = [](unsigned long value) {
  if (value < small_capital_boundary) {
    return static_cast<char>(value + small_letter_offset);
  }
  return static_cast<char>(value + capital_letter_offset);
};



} // namespace

int main() {
  unsigned long compartment_index{};

  std::array<std::array<unsigned long, compartment_size>, 3> compartments{};


const auto get_count = [&compartment_index, &compartments](const auto &line) -> unsigned long{
    unsigned long count{};
    std::string_view lineinput{line.begin(), line.end()};

    for (const char index : lineinput) {
      auto char_index =
          calculate_index(static_cast<unsigned char>(index));

      compartments.at(compartment_index).at(char_index)++;
    }

    fmt::print(" Input {} : {}\n", compartment_index, lineinput);

    if (compartment_index < 2) {
      compartment_index++;
      return {};
    }

    for (unsigned long index = 1; index < compartment_size; ++index) {
      if (compartments.at(0).at(index) > 0 &&
          compartments.at(1).at(index) > 0 &&
          compartments.at(2).at(index) > 0) {
        count += index;
        fmt::print("Found character : {} \tWith Count : {} \n\n",
                   calculate_char(index), index);
        break;
      }
    }
    compartment_index = 0;
    compartments.at(0).fill(0);
    compartments.at(1).fill(0);
    compartments.at(2).fill(0);

    return count;
};

  auto lines = std::string_view{inputdata} | std::views::split(line_delimiter) | std::views::transform(get_count) |std::views::common;

  const auto count = std::accumulate(lines.begin(), lines.end(), ::size_t{});
  
  fmt::print("Final Count = {}\n", count);
}
