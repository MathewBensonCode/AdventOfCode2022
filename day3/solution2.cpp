#include "input3.hpp"
#include <array>
#include <fmt/core.h>
#include <ranges>

namespace {
const auto compartment_size{53};
const auto small_letter_offset{96};
const auto capital_letter_offset{38};
const auto small_capital_boundary{27};

constexpr std::string_view line_delimiter{"\n"};
} // namespace

int main() {

  auto lines = inputdata | std::views::all | std::views::split(line_delimiter);

  std::size_t count{};

  std::size_t compartment_index{};

  std::array<std::array<std::size_t, compartment_size>, 3> compartments{};

  auto calculate_index = [](unsigned char letter) {
    auto value = static_cast<std::size_t>(letter);

    if (value > small_letter_offset) {
      return value - small_letter_offset;
    }
    return value - capital_letter_offset;
  };

  auto calculate_char = [](std::size_t value) {
    if (value < small_capital_boundary) {
      return static_cast<char>(value + small_letter_offset);
    }
    return static_cast<char>(value + capital_letter_offset);
  };

  for (const auto &line : lines) {
    std::string_view lineinput{line.begin(), line.end()};

    auto linelength = lineinput.size();
    if (linelength == 0) {
      fmt::print("empty string\n");
      break;
    };

    for (std::size_t index = 0; index < linelength; ++index) {
      auto char_index =
          calculate_index(static_cast<unsigned char>(lineinput[index]));

      compartments.at(compartment_index).at(char_index)++;
    }

    fmt::print(" Input {} : {}\n", compartment_index, lineinput);

    if (compartment_index < 2) {
      compartment_index++;
      continue;
    }

    for (std::size_t index = 1; index < compartment_size; ++index) {
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
    compartments[0].fill(0);
    compartments[1].fill(0);
    compartments[2].fill(0);
  }
  fmt::print("Final Count = {}\n", count);
}
