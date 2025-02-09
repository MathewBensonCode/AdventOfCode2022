#include "input5.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

int main()
{
  std::stringstream inputstringstream{ inputdata };

  std::size_t line_counter{ 0 };
  const std::size_t number_of_stacks{ 9 };
  const std::size_t data_line_end{ 8 };
  const std::size_t move_line_length{ 20 };
  std::size_t stack_location{ data_line_end - 1 };

  std::array<std::vector<char>, number_of_stacks> crate_containers{};

  auto fill_stacks = [&](const std::string &crate_data) {
    const auto stride{ 4 };

      for (std::size_t line_index{ 0 }; line_index < data_line_end + 1;
        ++line_index) {
        char value = crate_data.substr(1 + (line_index * stride), 1)[0];
          if (value != ' ') {
            auto &crate = crate_containers.at(line_index);
              if (crate.size() < stack_location) {
                crate.resize(stack_location + 1);
            }
            crate.at(stack_location) = value;
        }
        std::cout << value << ' ';
      }
    stack_location--;
    std::cout << '\n';
  };

  auto print_top_values = [&crate_containers] {
    std::cout << "\nTop Values => ";
      for (auto &stack : crate_containers) {
          if (!stack.empty()) {
            std::cout << stack.back() << ' ';
          } else {
            std::cout << "  ";
          }
      }
    std::cout << "\n\n";
  };

  auto print_stacks = [&crate_containers] {
    std::cout << "\nStacks => \n";

    std::size_t counter{ 1 };
      for (const auto &stack : crate_containers) {
        std::cout << "Stack " << counter << " => ";
          for (auto crate : stack) {
            std::cout << " | " << crate;
          }
        counter++;
        std::cout << '\n';
      }
  };

  auto move_crates = [&crate_containers](const std::string &move_instructions) {
    std::stringstream movestream{ move_instructions };

    std::string movestring;
    movestream >> movestring;
    std::size_t number_of_moves{};
    movestream >> number_of_moves;

    std::cout << '\n'
              << movestring << ' ' << number_of_moves << ' ';

    std::string from_string{};
    movestream >> from_string;
    std::size_t from_index{};

    movestream >> from_index;
    std::cout << from_string << ' ' << from_index << ' ';

    std::string to_string{};
    movestream >> to_string;
    std::size_t to_index{};
    movestream >> to_index;

    std::cout << to_string << ' ' << to_index << '\n';

      for (std::size_t index{ 0 }; index < number_of_moves; ++index) {
        auto &from_stack = crate_containers.at(from_index - 1);
        auto &to_stack = crate_containers.at(to_index - 1);

          if (!from_stack.empty()) {
            auto value = from_stack.back();
            to_stack.push_back(value);
            from_stack.pop_back();
          } else {
            std::cout << "\t\t\t----> From Stack Empty\n";
          }
      }
  };

    while (!inputstringstream.eof()) {
      std::string linestring{};

      std::getline(inputstringstream, linestring);

        if (linestring.length() == 0) {
          continue;
      }

        if (line_counter < data_line_end) {
          fill_stacks(linestring);
          line_counter++;
          continue;
      }

        if (linestring.length() > move_line_length) {
          print_top_values();
          continue;
      }

      move_crates(linestring);
      line_counter++;
      print_stacks();
      print_top_values();
    }
}
