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

  std::size_t compartment_index{};

  std::array<std::array<unsigned int, 53>, 3> compartments{};

  auto calculate_index = [](char letter) {
    unsigned int value = static_cast<unsigned int>(letter);

    if (value > 96) {
      return value - 96;
    }
    return value - 38;
  };

  auto calculate_char = [](unsigned int value) {
    if (value < 27) {
      return static_cast<char>(value + 96);
    }
    return static_cast<char>(value + 38);
  };

  while (!inputfile.eof()) {
    std::string lineinput{};

    std::getline(inputfile, lineinput);

    auto linelength = lineinput.size();
    if (linelength == 0) {
      std::cout << "empty string\n";
      break;
    };

    for (unsigned int index = 0; index < linelength; ++index) {
      auto char_index = calculate_index(lineinput[index]);

      compartments[compartment_index][char_index]++;
    }

    std::cout << " Input " << compartment_index << " : " << lineinput << '\n';

    if (compartment_index < 2) {
      compartment_index++;
      continue;
    }

    for (unsigned int index = 1; index < 53; ++index) {
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
