#include "input3.hpp"
#include <array>
#include <iostream>
#include <sstream>

int main() {
  std::stringstream inputstringstream{inputdata};

  const auto compartment_size{53};
  const auto small_letter_offset{96};
  const auto capital_letter_offset{38};
  const auto small_capital_boundary{27};

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

  while (!inputstringstream.eof()) {
    std::string lineinput{};

    std::getline(inputstringstream, lineinput);

    auto linelength = lineinput.size();
    if (linelength == 0) {
      std::cout << "empty string\n";
      break;
    };

    for (std::size_t index = 0; index < linelength; ++index) {
      auto char_index = calculate_index(static_cast<unsigned char>(lineinput[index]));

      compartments[compartment_index][char_index]++;
    }

    std::cout << " Input " << compartment_index << " : " << lineinput << '\n';
    if (compartment_index < 2) {
      compartment_index++;
      continue;
    }

    for (std::size_t index = 1; index < compartment_size; ++index) {
      if (compartments[0][index] > 0 && compartments[1][index] > 0 &&
          compartments[2][index] > 0) {
        count += index;
        std::cout << "Found character : " << calculate_char(index)
                  << "\tWith Count : " << index << '\n';
        break;
      }
    }
    compartment_index = 0;
    compartments[0].fill(0);
    compartments[1].fill(0);
    compartments[2].fill(0);
  }
  std::cout << "Final Count = " << count << '\n';
}
