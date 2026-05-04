#include "input10.hpp"
#include <array>
#include <sstream>
#include <print>
#include <string>

int main()
{
  std::istringstream inputstringstream{ inputdata };

  const unsigned screen_width{ 40 };
  const unsigned screen_height{ 6 };
  unsigned cycle_counter{};
  unsigned sprite_start_location{};

  std::array<std::array<char, screen_width>, screen_height> pixel_array{};

  auto draw_pixel = [&] {
    const unsigned current_row = cycle_counter / screen_width;
    const unsigned current_column = cycle_counter % screen_width;
    char current_char{ '.' };

      if ((current_column >= sprite_start_location) && (current_column <= sprite_start_location + 2)) {
        current_char = '#';
    }

    pixel_array.at(current_row).at(current_column) = current_char;
    cycle_counter++;
  };

    while (!inputstringstream.eof() || cycle_counter <= (screen_width * (screen_height - 1))) {
      std::string command{};
      inputstringstream >> command;

        if (command == "noop") {
          draw_pixel();
      }

        if (command == "addx") {
          draw_pixel();
          draw_pixel();
          unsigned add_value{};
          inputstringstream >> add_value;
          sprite_start_location += add_value;
          std::print("sprite_start_location => {}\n", sprite_start_location);
      }
    }

    for (auto &row : pixel_array) {
        for (auto &character : row) {
          std::print("{}", character);
        }
      std::print("\n");
    }
}
