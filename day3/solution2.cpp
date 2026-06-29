#include "input3.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
  std::stringstream inputstringstream{ inputdata };

  const char compartment_size{ 53 };
  const char small_letter_offset{ 96 };
  const char capital_letter_offset{ 38 };
  const char small_capital_boundary{ 27 };

  auto count{ 0U };

  auto compartment_index{ 0U };

  std::array<std::array<unsigned, compartment_size>, 3> compartments{};

  auto calculate_index = [](const char value) -> unsigned char {
    if (value > small_letter_offset) {
      return static_cast<unsigned char>(value - small_letter_offset);
  }
  return static_cast<unsigned char>(value - capital_letter_offset);
  };

  auto calculate_char = [](const char value) {
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

        for (auto index = 0U; index < linelength; ++index) {
          auto char_index = calculate_index(lineinput.at(index));

          compartments.at(compartment_index).at(char_index)++;
        }

      std::cout << " Input " << compartment_index << " : " << lineinput << '\n';
        if (compartment_index < 2) {
          compartment_index++;
          continue;
      }

        for (unsigned char index = 1; index < compartment_size; ++index) {
            if (compartments.at(0).at(index) > 0 && compartments.at(1).at(index) > 0 && compartments.at(2).at(index) > 0) {
              count += index;
              std::cout << "Found character : " << calculate_char(static_cast<char>(index))
                        << "\tWith Count : " << index << '\n';
              break;
          }
        }
      compartment_index = 0;
      compartments.at(0).fill(0);
      compartments.at(1).fill(0);
      compartments.at(2).fill(0);
    }
  std::cout << "Final Count = " << count << '\n';
}
