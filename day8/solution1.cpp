import input8;
import std;

int main() {
  std::stringstream inputstringstream{inputdata};
  const auto array_width{99};
  const auto counter_length{array_width * array_width};
  std::array<std::array<char, array_width>, array_width> datastore{};
  std::array<std::array<char, array_width>, array_width> printstore{};
  std::array<std::size_t, counter_length> visible_tree_count_store{};

  auto get_index_for_array = [](std::size_t row,
                                std::size_t col) -> std::size_t {
    return col + (row * array_width);
  };

  auto print_found = [&](const std::string &name) {
    std::cout << name << '\n';
    for (std::size_t row_index{0}; row_index < array_width; ++row_index) {
      for (std::size_t col_index{0}; col_index < array_width; ++col_index) {
        std::cout << printstore.at(row_index).at(col_index);
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  };

  auto read_data = [&inputstringstream, &datastore] {
    for (std::size_t row_index{0}; row_index < array_width; ++row_index) {
      for (std::size_t col_index{0}; col_index < array_width; ++col_index) {
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
    for (std::size_t row_index{0}; row_index < array_width; ++row_index) {
      char highest_tree{};
      for (std::size_t col_index{0}; col_index < array_width; ++col_index) {
        const auto current_tree = datastore.at(row_index).at(col_index);

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
    for (std::size_t col_index{0}; col_index < array_width; ++col_index) {
      char highest_tree{};
      for (std::size_t row_index{0}; row_index < array_width; ++row_index) {
        char current_tree = datastore.at(row_index).at(col_index);

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
    for (auto row_index{0}; row_index < array_width; ++row_index) {
      char highest_tree{};
      for (auto col_index{array_width - 1}; col_index >= 0; --col_index) {
        auto rowval = static_cast<std::size_t>(row_index);
        auto colval = static_cast<std::size_t>(col_index);
        const auto current_tree = datastore.at(rowval).at(colval);

        if ((colval == array_width) || (current_tree > highest_tree)) {
          highest_tree = current_tree;
          visible_tree_count_store.at(get_index_for_array(rowval, colval))++;
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
    for (auto col_index{0}; col_index < array_width; ++col_index) {
      char highest_tree{};
      for (auto row_index{array_width - 1}; row_index >= 0; --row_index) {
        auto rowval = static_cast<std::size_t>(row_index);
        auto colval = static_cast<std::size_t>(col_index);
        const auto current_tree = datastore.at(rowval).at(colval);

        if ((rowval == array_width) || (current_tree > highest_tree)) {
          highest_tree = current_tree;
          visible_tree_count_store.at(get_index_for_array(rowval, colval))++;
          printstore.at(rowval).at(colval) = current_tree;
          continue;
        }
        printstore.at(rowval).at(colval) = ' ';
      }
    }
    print_found("Bottom To Top");
  };

  count_trees_bottom_to_top();

  const auto visible_tree_count = std::ranges::count_if(
      visible_tree_count_store, [](const auto tree) { return tree > 0; });

  std::cout << "\nViewable Trees => " << visible_tree_count << '\n';
}
