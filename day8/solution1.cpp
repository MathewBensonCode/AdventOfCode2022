#include "input8.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string_view>
#include <exception>
#include <format>

int main()
{
    try {
      std::stringstream inputstringstream{ inputdata };
      const unsigned array_width{ 99 };
      const unsigned counter_length{ array_width * array_width };
      std::array<std::array<char, array_width>, array_width> datastore{};
      std::array<std::array<char, array_width>, array_width> printstore{};
      std::array<unsigned, counter_length> visible_tree_count_store{};

      auto get_index_for_array = [](unsigned row,
                                   unsigned col) -> unsigned {
        return col + (row * array_width);
      };

      auto print_found = [&](const std::string_view name) {
        std::cout << name << '\n';
          for (unsigned row_index{ 0 }; row_index < array_width; ++row_index) {
              for (unsigned col_index{ 0 }; col_index < array_width; ++col_index) {
                std::cout << printstore.at(row_index).at(col_index);
              }
            std::cout << '\n';
          }
        std::cout << '\n';
      };

      auto read_data = [&inputstringstream, &datastore] {
        for (unsigned row_index{ 0 }; row_index < array_width; ++row_index) {
            for (unsigned col_index{ 0 }; col_index < array_width; ++col_index) {
              char value{};
              inputstringstream >> value;
              datastore.at(row_index).at(col_index) = value;
              std::cout << value;
            }

          std::cout << '\n';
        }
      std::cout << '\n';
      };

      read_data();

      auto count_trees_left_to_right = [&]() {
        for (unsigned row_index{ 0 }; row_index < array_width; ++row_index) {
          char highest_tree{};
          char current_tree{};
            for (unsigned col_index{ 0 }; col_index < array_width; ++col_index) {
              current_tree = datastore.at(row_index).at(col_index);

                if ((col_index == 0) || (current_tree > highest_tree)) {
                  highest_tree = current_tree;
                  visible_tree_count_store.at(
                    get_index_for_array(row_index, col_index))++;
                  printstore.at(row_index).at(col_index) = current_tree;
                  continue;
              }
              printstore.at(row_index).at(col_index) = ' ';
            }
        }
      print_found("Left To Right");
      };

      count_trees_left_to_right();

      auto count_trees_top_to_bottom = [&]() {
        for (unsigned col_index{ 0 }; col_index < array_width; ++col_index) {
          char highest_tree{};
          char current_tree{};
            for (unsigned row_index{ 0 }; row_index < array_width; ++row_index) {
              current_tree = datastore.at(row_index).at(col_index);

                if ((row_index == 0) || (current_tree > highest_tree)) {
                  highest_tree = current_tree;
                  visible_tree_count_store.at(
                    get_index_for_array(row_index, col_index))++;
                  printstore.at(row_index).at(col_index) = current_tree;
                  continue;
              }
              printstore.at(row_index).at(col_index) = ' ';
            }
        }
      print_found("Top To Bottom");
      };

      count_trees_top_to_bottom();

      auto count_trees_right_to_left = [&]() {
        for (unsigned row_index{ 0 }; row_index < array_width; ++row_index) {
          char highest_tree{};
          char current_tree{};
            for (unsigned col_index{ array_width - 1 }; col_index != unsigned{}; --col_index) {
              auto rowval = row_index;
              auto colval = col_index;
              current_tree = datastore.at(rowval).at(colval);

                if ((colval == array_width) || (current_tree > highest_tree)) {
                  highest_tree = current_tree;
                  visible_tree_count_store.at(
                    get_index_for_array(rowval, colval))++;
                  printstore.at(rowval).at(colval) = current_tree;
                  continue;
              }
              printstore.at(rowval).at(colval) = ' ';
            }
        }
      print_found("Right To Left");
      };

      count_trees_right_to_left();

      auto count_trees_bottom_to_top = [&]() {
        for (unsigned col_index{}; col_index < array_width; ++col_index) {
          char highest_tree{};
          char current_tree{};
            for (unsigned row_index{ array_width - 1 }; row_index != unsigned{}; --row_index) {
              auto rowval = row_index;
              auto colval = col_index;
              current_tree = datastore.at(rowval).at(colval);

                if ((rowval == array_width) || (current_tree > highest_tree)) {
                  highest_tree = current_tree;
                  visible_tree_count_store.at(
                    get_index_for_array(rowval, colval))++;
                  printstore.at(rowval).at(colval) = current_tree;
                  continue;
              }
              printstore.at(rowval).at(colval) = ' ';
            }
        }
      print_found("Bottom To Top");
      };

      count_trees_bottom_to_top();

      unsigned visible_tree_count{};

        for (auto &tree : visible_tree_count_store) {
            if (tree > 0) {
              visible_tree_count++;
          }
        }
      std::cout << "\nViewable Trees => " << visible_tree_count << '\n';
    } catch (std::exception &e) {
      std::cerr << std::format("Exception : {}\n", e.what());
  }
}
