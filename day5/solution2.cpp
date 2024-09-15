import input5;
import std;
import module5;

using namespace day5;

const auto process_moves = [](const auto moves, auto &stack_container) {
  auto lines = moves | std::views::split(line_delimiter) |
               std::views::transform(to_string_view{});

  auto getnum = [](const auto text) {
    int current_num{-1};
    std::from_chars(text.data(), text.data() + text.size(), current_num);
    return current_num;
  };

  for (const auto line : lines) {
    auto values = line | std::views::split(space_delimiter) |
                  std::views::transform(to_string_view{}) |
                  std::views::transform(getnum) |
                  std::views::filter([](const auto num) { return num > 0; });

    auto starting_point = values.begin();
    const auto number_of_moves = static_cast<std::size_t>(*starting_point);
    std::advance(starting_point, 1);
    const auto from_stack_number = static_cast<std::size_t>(*starting_point);
    std::advance(starting_point, 1);
    const auto to_stack_number = static_cast<std::size_t>(*starting_point);

    auto &from_container_stack = stack_container.at(from_stack_number - 1);
    auto &to_container_stack = stack_container.at(to_stack_number - 1);

    std::vector<char> tempcontainer(number_of_moves);

    auto move_crate_values = [](auto &from_stack, auto moves_number,
                                auto &to_stack) {
      for (std::size_t index{0}; index < moves_number; ++index) {

        if (!from_stack.empty()) {
          auto value = from_stack.back();
          to_stack.push_back(value);
          from_stack.pop_back();
        } else {
          std::print("\t\t\t----> From Stack Empty\n");
        }
      }
    };

    move_crate_values(from_container_stack, number_of_moves, tempcontainer);
    move_crate_values(tempcontainer, number_of_moves, to_container_stack);

    std::print("\nAfter move {} crates from stack {} to stack {} \n",
               number_of_moves, from_stack_number, to_stack_number);
    print_stacks(stack_container);
  }
};

int main() {
  auto sections = inputdata |
                  std::views::split(section_delimiter) |
                  std::views::transform(to_string_view{});

  const auto data_section = sections.front();

  std::array<std::vector<char>, stack_count> data_store{};

  for (auto &vec : data_store) {
    vec.reserve(stack_count);
  }

  std::print("Original Values => {}\n\n", data_section);

  fill_stacks(std::string_view{data_section.begin(), data_section.end()},
              data_store);

  const auto move_section = *(std::next(sections.begin()));

  process_moves(move_section, data_store);

  std::print("\nTop Values => ");
  for (const auto &stack : data_store) {
    auto top_value = stack.back();
    std::print("{}|", top_value);
  }
}
