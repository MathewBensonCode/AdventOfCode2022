#include "input3.hpp"
#include <array>
#include <iostream>
#include <ranges>

namespace {
const auto compartment_size{53};
const auto small_letter_offset{96};
const auto capital_letter_offset{38};
const auto small_capital_boundary{27};
constexpr std::string_view line_delimiter{"\n"};

const auto calculate_char = [](std::size_t value) {
  if (value < small_capital_boundary) {
    return static_cast<unsigned char>(value + small_letter_offset);
  }
  return static_cast<unsigned char>(value + capital_letter_offset);
};

const auto calculate_index = [](unsigned char letter) {
  auto value = static_cast<std::size_t>(letter);

  if (value > small_letter_offset) {
    return value - small_letter_offset;
  }
  return value - capital_letter_offset;
};

} // namespace

int main() {

  std::size_t count{};

  auto lines = inputdata | std::views::split(line_delimiter);

  for (const auto &line : lines) {
    std::string_view lineinput{line.begin(), line.end()};

    auto halflength = lineinput.size() / 2;

    std::array<std::size_t, compartment_size> first_compartment{};
    std::array<std::size_t, compartment_size> second_compartment{};

    auto first_half = lineinput.substr(0, halflength);
    auto second_half = lineinput.substr(halflength);

    std::cout << "\nLine input : \n" << lineinput << '\n';
    std::cout << "First_Half => " << first_half << '\n';
    std::cout << "Second_Half => " << second_half << '\n';

    for (std::size_t index = 0; index < halflength; ++index) {
      const auto first_half_char_index =
          calculate_index(static_cast<unsigned char>(first_half[index]));
      const auto second_half_char_index =
          calculate_index(static_cast<unsigned char>(second_half[index]));

      first_compartment.at(first_half_char_index)++;
      second_compartment.at(second_half_char_index)++;
    }

    for (std::size_t index = 1; index < compartment_size; ++index) {
      if (first_compartment.at(index) > 0 && second_compartment.at(index) > 0) {
        count += index;
        std::cout << "Found character : " << calculate_char(index)
                  << "\tWith Count : " << index << '\n';
      }
    }
  }

  std::cout << "Final Count = " << count << '\n';
}
