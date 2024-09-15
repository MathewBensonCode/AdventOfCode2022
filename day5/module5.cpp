export module module5;

import std;

export namespace day5 {
constexpr std::string_view section_delimiter{"\n\n"};
constexpr std::string_view line_delimiter{"\n"};
constexpr std::string_view space_delimiter{" "};
constexpr auto stack_count{9};
constexpr auto stride{4};

struct to_string_view {
  auto operator()(const auto &data) {
    return std::string_view{data.begin(), data.end()};
  }
};

auto fill_stacks(const std::string_view datasection, auto &stack_container) {
  auto lines = datasection | std::views::split(line_delimiter) |
               std::views::take(stack_count) |
               std::views::transform(to_string_view{});

  for (const auto &line : lines) {
    const auto *itr = line.begin();
    std::size_t stack_counter{};
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
}

auto print_stacks(const auto &stack_container) {
  std::print("\nStack Status\n");
  auto stack_number{1};
  for (const auto &vec : stack_container) {
    std::print("{} =>|", stack_number);
    for (const auto box : vec) {
      std::print("{}|", box);
    }
    std::print("\n");
    stack_number++;
  }

  std::print("\nTop Values => ");

  for (const auto &vec : stack_container) {
    if (!vec.empty()) {
      std::print("{}|", vec.back());
      continue;
    }
    std::print(" |");
  }

  std::print("\n--------\n\n");
}

} // namespace day5
