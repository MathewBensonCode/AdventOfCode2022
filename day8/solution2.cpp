#include "input8.hpp"
import std;

using namespace std::string_view_literals;

namespace day8
{

const auto array_width{ 99 };

auto get_columns(auto &rowview, const auto row, const auto column)
{
  return rowview | std::views::drop(row) | std::views::drop(1) | std::views::transform([column](const auto &row) {
    auto iterator = row.begin();
    std::advance(iterator, column);
    return *iterator;
  }) | std::views::take(array_width-(row+1));
}

auto get_reverse_columns(auto &dataview, const std::size_t row, const std::size_t column)
{
  return dataview | std::views::reverse | std::views::split("\n"sv) | std::views::drop(1) | std::views::drop(array_width - (row+1))| std::views::transform([column](const auto &row) {
    auto iterator = row.begin();
    std::advance(iterator, (array_width - (column + 1)));
    return *iterator;
  }) | std::views::take(row-1);
}


}// namespace day8

using namespace day8;

int main()
{
  auto dataview = std::string_view{ inputdata } | std::views::drop(1);
  auto rowview = dataview | std::views::split("\n"sv);
  auto print_current = [](char current) { std::cout << " => " << current << " -> "; };

  std::size_t highest_scenic_score{};

  unsigned row_index{};
    for (const auto &row : rowview) {
      unsigned col_index{};
        for (const auto &column : row) {

            const auto current = column - '0';

          std::cout << "Row = " << row_index << "\t| Col = " << col_index << '\n';

          std::cout << "Left to Right";
          bool found_one_already{ false };
          auto lines_ltr = row | std::views::drop(col_index + 1) | std::views::take_while([&found_one_already, current](const auto next) {
                  auto nextint = next - '0';
            if (!found_one_already) {
                if (nextint < current) {
                  std::cout << nextint;
                  return true;
              }
                if (nextint == current) {
                  std::cout << nextint;
                  found_one_already = true;
                  return true;
              }
          }
          std::cout << "/" << nextint << "/";
          return false;
          });

          print_current(column);

          unsigned ltrsize{};
          for(const auto& counter: lines_ltr){
              ltrsize++;
          }

          std::cout << " | count = " << ltrsize << '\n';

          std::cout << "Right to Left";
          found_one_already = false;
          auto lines_rtl = row | std::views::reverse | std::views::drop(array_width - col_index) | std::views::take_while([&found_one_already, current ](const auto next) {
                  auto nextint = next - '0';
            if (!found_one_already) {
                if (nextint < current) {
                  std::cout << nextint;
                  return true;
              }
                if (next == current) {
                  std::cout << nextint;
                  found_one_already = true;
                  return true;
              }
          }
          std::cout << "/" << nextint << "/";
          return false;
          });

          print_current(column);

          unsigned rtlsize{};
          for(const auto& counter: lines_rtl){
              rtlsize++;
          }

          std::cout << " | count = " << rtlsize << '\n';

          std::cout << "Top to Bottom";
          found_one_already = false;
          auto lines_ttb = get_columns(rowview, row_index, col_index) | std::views::take_while([&found_one_already, current](const auto next) {
            const auto nextint = next - '0';
            if (!found_one_already) {
                if (nextint < current) {
                  std::cout << nextint;
                  return true;
              }
                if (nextint == current) {
                  std::cout << nextint;
                  found_one_already = true;
                  return true;
              }
          }
          std::cout << "/" << nextint << "/";
          return false;
          });

          print_current(column);

          unsigned ttbsize{};
          for(const auto& counter: lines_ttb){
              ttbsize++;
          }

          std::cout << " | count = " << ttbsize << '\n';

          std::cout << "Bottom to Top";

          found_one_already = false;
          auto lines_btt = get_reverse_columns(dataview, row_index, col_index) | std::views::drop(1) | std::views::take_while([&found_one_already, current](const auto next) {
            const auto nextint = next - '0';
            if (!found_one_already) {
                if (nextint < current) {
                  std::cout << nextint;
                  return true;
              }
                if (nextint == current) {
                  std::cout << nextint;
                  found_one_already = true;
                  return true;
              }
          }
          std::cout << "/" << nextint << "/";
          return false;
          });
          print_current(column);

          unsigned bttsize{};
          for(const auto& counter: lines_btt){
              bttsize++;
          }
          std::cout << " | count = " << bttsize << '\n';

          std::cout << "\n----\n";

          auto scenic_score = (ltrsize * rtlsize * ttbsize * bttsize);

            if (scenic_score > highest_scenic_score) {
              highest_scenic_score = static_cast<std::size_t>(scenic_score);
          }
          col_index++;
        }
      std::cout << '\n';
      row_index++;
    }
  std::cout << " Highest Scenic Score ==> " << highest_scenic_score << '\n';
}
