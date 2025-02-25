import input5;
import std;
import module5;

auto process_moves = [](const auto &moves, auto &stack_container) {
  auto lines = moves | std::views::split(line_delimiter) |
               std::views::transform(to_string_view{});

  auto getnum = [](const auto text) {
    int current_num{-1};
    std::from_chars(text.data(), text.data() + text.size(), current_num);
    return current_num;
  };

  for (const auto& line : lines) {
    auto values = line | std::views::split(space_delimiter) |
                  std::views::transform(to_string_view{}) |
                  std::views::transform(getnum) |
                  std::views::filter([](const auto num) { return num > 0; });

    auto starting_point = values.begin();
    const auto number_of_moves = *starting_point;
    std::advance(starting_point, 1);
    const auto from_stack_number = *starting_point;
    std::advance(starting_point, 1);
    const auto to_stack_number = *starting_point;

    for (auto index{0}; index < number_of_moves; ++index) {
      auto &from_vec =
          stack_container.at(static_cast<unsigned>(from_stack_number - 1));
      auto value = from_vec.back();
      from_vec.pop_back();

      auto &to_vec =
          stack_container.at(static_cast<unsigned>(to_stack_number - 1));
      to_vec.push_back(value);
    }
    std::print("\nAfter {} ", line);
    print_stacks(stack_container);
  }
};


int main() {
  auto sections = std::string_view{inputdata} |
                  std::views::split(section_delimiter) |
                  std::views::transform(to_string_view{});

  const auto data_section = sections.front();

  std::array<std::vector<char>, stack_count> data_store{};

  for (auto &vec : data_store) {
    vec.reserve(stack_count);
  }

  std::print("Original Values => {}\n\n", data_section);

  fill_stacks({data_section.begin(), data_section.end()},
              data_store);

  const auto move_section = *(std::next(sections.begin()));

  process_moves(move_section, data_store);

  std::print("\nTop Values => ");
  for (const auto &stack : data_store) {
    auto top_value = stack.back();
    std::print("{}|", top_value);
  }

  std::print("\n");
}
