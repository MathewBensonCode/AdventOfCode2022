#include "fmt/core.h"
#include "input10.hpp"
#include <sstream>

int main() {
  std::istringstream inputstringstream{inputdata};

  const int cycle_start_point{20};
  const int cycle_increment{40};
  int cycle_counter{};
  int next_cycle_point{cycle_start_point};
  int register_value{1};
  int register_value_sum{};

  auto add_counter = [&] {
    cycle_counter++;

    if (cycle_counter == next_cycle_point) {
      auto current_register_sum = next_cycle_point * register_value;
      register_value_sum += current_register_sum;
      fmt::print("\tWith Cycles at {} & Register at {}, current Signal => {} "
                 "\t and Sum of Signals => {}\n",
                 cycle_counter, register_value, current_register_sum,
                 register_value_sum);
      next_cycle_point += cycle_increment;
    }
  };

  while (!inputstringstream.eof()) {
    std::string command{};
    inputstringstream >> command;

    if (command == "noop") {
      fmt::print("{}\n", command);
      add_counter();
    }

    if (command == "addx") {
      add_counter();
      add_counter();
      int add_value{};
      inputstringstream >> add_value;
      register_value += add_value;
      fmt::print("{} -> {} | register_value = {}\n", command, add_value,
                 register_value);
    }
  }
}
