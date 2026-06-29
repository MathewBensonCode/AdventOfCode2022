#include <array>
#include <string>
#include <sstream>
#include <iostream>
#include "input3.hpp"

int main()
{
  std::stringstream inputstringstream{ inputdata };

    if (!inputstringstream) {
      std::cerr << "File Not Found\n";
      return 1;
  }

  auto count{ 0U };

    while (!inputstringstream.eof()) {
      std::string lineinput{};

      std::getline(inputstringstream, lineinput);

      auto linelength = lineinput.size();
        if (linelength == 0) {
          std::cout << "empty string\n";
          break;
      };

      const auto halflength = static_cast<unsigned char>(linelength / 2);

      const unsigned char compartment_size{ 53U };
      const char small_letter_offset{ 96 };
      const char capital_letter_offset{ 38 };
      const char small_capital_boundary{ 27 };

      std::array<unsigned, compartment_size> first_compartment{};
      std::array<unsigned, compartment_size> second_compartment{};

      auto first_half = lineinput.substr(0, halflength);
      auto second_half = lineinput.substr(halflength);

      auto calculate_index = [](const char value) -> unsigned {
        if (value > small_letter_offset) {
          return static_cast<unsigned>(value - small_letter_offset);
      }
      return static_cast<unsigned>(value - capital_letter_offset);
      };

      std::cout << "\nLine input : \n"
                << lineinput << '\n';
      std::cout << "First_Half => " << first_half << '\n';
      std::cout << "Second_Half => " << second_half << '\n';

        for (unsigned char index{}; index < halflength; ++index) {

          const auto first_half_char_index = calculate_index(first_half.at(index));
          const auto second_half_char_index = calculate_index(second_half.at(index));

          first_compartment.at(first_half_char_index)++;
          second_compartment.at(second_half_char_index)++;
        }

      auto calculate_char = [](const auto value) {
        if (value < small_capital_boundary) {
          return (value + small_letter_offset);
      }
      return (value + capital_letter_offset);
      };

        for (unsigned index = 1; index < compartment_size; ++index) {
            if (first_compartment.at(index) > 0 && second_compartment.at(index) > 0) {
              count += index;
              std::cout << "Found character : " << calculate_char(index)
                        << "\tWith Count : " << index << '\n';
          }
        }
    }

  std::cout << "Final Count = " << count << '\n';
}
