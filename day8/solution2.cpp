#include "input8.hpp"
import std;

int main() {
  constexpr std::string_view dataview{inputdata};
  constexpr std::string_view delim{"\n"};

  const auto array_width{99};

  auto split_view = dataview | std::views::split(delim) | std::views::drop(1) |
                    std::views::take(array_width);

  auto reverse_split_view = dataview | std::views::reverse |
                            std::views::split(delim) | std::views::drop(1) |
                            std::views::take(array_width);
  auto joint_view = split_view | std::views::join;

  bool found_one_already{};
  char current{};

  auto find_trees_less = [&current, &found_one_already](char next) -> bool {
    if (!found_one_already) {
      if (next < current) {
        return true;
      }
      if (next == current) {
        found_one_already = true;
        return true;
      }
    }
    return false;
  };

  auto get_left_to_right_view = [&](std::size_t row, std::size_t col) -> auto{
    auto current_view = joint_view |
                        std::views::drop((row * array_width) + col) |
                        std::views::take(array_width - col);

    auto curr = current_view.begin();
    current = *curr;

    std::vector<char> results{};

    found_one_already = false;
    auto calculate_view = current_view | std::views::drop(1) |
                          std::views::take_while(find_trees_less);

    std::ranges::copy(calculate_view, std::back_inserter(results));

    return results;
  };

  auto get_right_to_left_view = [&](std::size_t row, std::size_t col) -> auto{
    std::vector<char> results{};

    auto rowviews = split_view | std::views::drop(row);

    auto myview = rowviews.begin();
    auto current_view =
        *myview | std::views::reverse | std::views::drop(array_width - col - 1);

    auto curr = current_view.begin();
    current = *curr;

    found_one_already = false;
    std::ranges::copy(current_view | std::views::drop(1) |
                          std::views::take_while(find_trees_less),
                      std::back_inserter(results));
    return results;
  };

  auto get_top_to_bottom_view = [&](std::size_t row, std::size_t col) -> auto{
    std::vector<char> results{};
    found_one_already = false;
    auto rowviews = split_view | std::views::drop(row);

    auto first_selected = *(rowviews.begin()) | std::views::drop(col);

    current = *(first_selected.begin());

    auto remaining_views = rowviews | std::views::drop(1);

    for (auto myrow : remaining_views) {
      auto selected = myrow | std::views::drop(col);

      auto value = *(selected.begin());
      if (find_trees_less(value)) {
        results.push_back(value);
        continue;
      }
      break;
    }

    return results;
  };

  auto get_bottom_to_top_view = [&](std::size_t row, std::size_t col) -> auto{
    std::vector<char> results{};
    auto rowviews =
        reverse_split_view | std::views::drop(array_width - (row + 1));

    auto first_selected =
        *(rowviews.begin()) | std::views::drop(array_width - (col + 1));

    current = *(first_selected.begin());
    found_one_already = false;

    auto remaining_views = rowviews | std::views::drop(1);

    for (auto myrow : remaining_views) {
      auto selected = myrow | std::views::drop(array_width - (col + 1));

      auto value = *(selected.begin());
      if (find_trees_less(value)) {
        results.push_back(value);
      } else {
        break;
      }
    }

    return results;
  };

  auto print_current = [&current] { std::cout << " => " << current << " -> "; };

  std::size_t highest_scenic_score{};

  for (std::size_t row_index{}; row_index < array_width; ++row_index) {
    for (std::size_t col_index{0}; col_index < array_width; ++col_index) {

      std::cout << "Row = " << row_index << "\t| Col = " << col_index << '\n';

      std::cout << "Left to Right";
      auto lines_ltr = get_left_to_right_view(row_index, col_index);

      print_current();
      for (auto line : lines_ltr) {
        std::cout << line;
      }
      std::cout << " | count = " << lines_ltr.size() << '\n';

      std::cout << "Right to Left";
      auto lines_rtl = get_right_to_left_view(row_index, col_index);

      print_current();
      for (auto line : lines_rtl) {
        std::cout << line;
      }
      std::cout << " | count = " << lines_rtl.size() << '\n';

      std::cout << "Top to Bottom";

      auto lines_ttb = get_top_to_bottom_view(row_index, col_index);

      print_current();
      for (auto line : lines_ttb) {
        std::cout << line;
      }

      std::cout << " | count = " << lines_ttb.size() << '\n';

      std::cout << "Bottom to Top";

      auto lines_btt = get_bottom_to_top_view(row_index, col_index);

      print_current();
      for (auto line : lines_btt) {
        std::cout << line;
      }

      std::cout << " | count = " << lines_btt.size() << '\n';

      std::cout << "\n----\n";

      auto scenic_score = lines_ltr.size() * lines_rtl.size() *
                          lines_ttb.size() * lines_btt.size();

      if (scenic_score > highest_scenic_score) {
        highest_scenic_score = scenic_score;
      }
    }
    std::cout << '\n';
  }
  std::cout << " Highest Scenic Score ==> " << highest_scenic_score << '\n';
}
