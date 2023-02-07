#include "input5.hpp"
#include <algorithm>
#include <array>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <iterator>
#include <ranges>
#include <string_view>
#include <vector>

namespace {
constexpr std::string_view section_delimiter{"\n\n"};
constexpr std::string_view line_delimiter{"\n"};
constexpr std::string_view space_delimiter{" "};
const auto stack_count{9};
constexpr auto stride{4};

const auto to_string_view = [](const auto &data) {
  return std::string_view{data.begin(), data.end()};
};

const auto fill_stacks = [](const std::string_view datasection,
                            auto &stack_container) {
  auto lines = datasection | std::views::split(line_delimiter) |
               std::views::take(stack_count) |
               std::views::transform(to_string_view);

  for (const auto &line : lines) {
    auto itr = line.begin();
    auto stack_counter{0};
    if (!line.empty()) {
      std::advance(itr, 1);

      while (std::distance(itr, line.end()) > 1) {
        const auto value = *itr;
        if (value != ' ') {
          stack_container.at(stack_counter).push_back(value);
        }

        if (std::distance(itr, line.end()) == 2) {
          break;
        }
        std::advance(itr, stride);
        stack_counter++;
      };
    }
  }

  for (auto &vec : stack_container) {
    std::ranges::reverse(vec);
  }
};

const auto print_stacks = [](const auto &stack_container) {
  fmt::print("\nStack Status\n");
  auto stack_number{1};
  for (const auto &vec : stack_container) {
    fmt::print("{} => {}\n", stack_number, vec);
    stack_number++;
  }

  fmt::print("\n--------\n\n");
};

const auto process_moves = [](const auto moves, auto &stack_container) {
  auto lines = moves | std::views::split(line_delimiter) |
               std::views::transform(to_string_view);

  for (const auto line : lines) {
    auto values = line | std::views::split(space_delimiter) |
                  std::views::drop(1) | std::views::take(1) |
                  std::views::drop(1) | std::views::take(1) |
                  std::views::drop(1) | std::views::take(1);

    fmt::print("I will Move {} from {} to {}", values.begin(), *(std::next(values.begin())), *(std::next(std::next(values.begin()))));
  }
};

} // namespace

int main() {
  auto sections = std::string_view{inputdata} |
                  std::views::split(section_delimiter) |
                  std::views::transform(to_string_view);

  const auto data_section = sections.front();

  std::array<std::vector<char>, stack_count> data_store{};

  for (auto &vec : data_store) {
    vec.reserve(stack_count);
  }

  fmt::print("Original Values => {}\n\n", data_section);

  fill_stacks(std::string_view{data_section.begin(), data_section.end()},
              data_store);

  print_stacks(data_store);

  const auto move_section = *(std::next(sections.begin()));

  process_moves(move_section, data_store);
}
