#include <array>
#include <fstream>
#include <iostream>

int main() {
  std::ifstream inputfile{"input"};

  if (!inputfile) {
    std::cerr << "File Not Found\n";
    return 1;
  }

  std::size_t count{};

  while (!inputfile.eof()) {
    std::string lineinput{};

    std::getline(inputfile, lineinput);

    auto linelength = lineinput.size();
    if (linelength == 0) {
      std::cout << "empty string\n";
      break;
    };

    auto halflength = linelength / 2;

    std::array<unsigned int, 53> first_compartment{};
    std::array<unsigned int, 53> second_compartment{};

    auto first_half = lineinput.substr(0, halflength);
    auto second_half = lineinput.substr(halflength);

    auto calculate_index = [](char letter) {
      unsigned int value = static_cast<unsigned int>(letter);

      if (value > 96) {
        return value - 96;
      }
      return value - 38;
    };

    std::cout << "\nLine input : \n" << lineinput << '\n';
    std::cout << "First_Half => " << first_half << '\n';
    std::cout << "Second_Half => " << second_half << '\n';

    for (unsigned int index = 0; index < halflength; ++index) {
      auto first_half_char_index = calculate_index(first_half[index]);
      auto second_half_char_index = calculate_index(second_half[index]);

      first_compartment[first_half_char_index]++;
      second_compartment[second_half_char_index]++;
    }

    auto calculate_char = [](unsigned int value) {
      if (value < 27) {
        return static_cast<char>(value + 96);
      }
      return static_cast<char>(value + 38);
    };

    for (unsigned int index = 1; index < 53; ++index) {
      if (first_compartment[index] > 0 && second_compartment[index] > 0) {
        count += index;
        std::cout << "Found character : " << calculate_char(index)
                  << "\tWith Count : " << index << '\n';
      }
    }
  }

  std::cout << "Final Count = " << count << '\n';
}
