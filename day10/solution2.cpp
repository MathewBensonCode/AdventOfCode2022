#include "input10.hpp"
import std;
import fmt;

int main() {
  std::istringstream inputstringstream{inputdata};

  const std::size_t screen_width{40};
  const std::size_t screen_height{6};
  std::size_t cycle_counter{};
  std::size_t sprite_start_location{};

  std::array<std::array<char, screen_width>, screen_height> pixel_array{};

  auto draw_pixel = [&] {
    std::size_t current_row = cycle_counter / screen_width;
    std::size_t current_column = cycle_counter % screen_width;
    char current_char{'.'};

    if ((current_column >= sprite_start_location) &&
        (current_column <= sprite_start_location + 2)) {
      current_char = '#';
    }

    pixel_array.at(current_row).at(current_column) = current_char;
    cycle_counter++;
  };

  while (!inputstringstream.eof() ||
         cycle_counter <= (screen_width * (screen_height - 1))) {
    std::string command{};
    inputstringstream >> command;

    if (command == "noop") {
      draw_pixel();
    }

    if (command == "addx") {
      draw_pixel();
      draw_pixel();
      std::size_t add_value{};
      inputstringstream >> add_value;
      sprite_start_location += add_value;
      fmt::print("sprite_start_location => {}\n", sprite_start_location);
    }
  }

  for (auto &row : pixel_array) {
    for (auto &character : row) {
      fmt::print("{}", character);
    }
    fmt::print("\n");
  }
}
