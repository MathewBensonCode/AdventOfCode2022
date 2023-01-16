#include "input11.hpp"
#include <algorithm>
#include <charconv>
#include <cstdint>
#include <fmt/core.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string_view>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecistion;
using checked_uint = number<cpp_int_backend<10240, 10240, unsigned_magnitude, checked, void>>;

namespace {
struct Monkey {
  std::vector<checked_uint> items{};
  std::function<checked_uint(checked_uint)> item_operation{};
  std::size_t test{};
  std::size_t true_monkey{};
  std::size_t false_monkey{};
};

constexpr std::string_view sectiondelimiter{"\n\n"};
constexpr std::string_view line_delimiter{"\n"};
constexpr std::string_view name_delimiter{": "};
constexpr std::string_view item_delimiter{", "};
constexpr std::string_view operation_delimiter{"= "};
constexpr std::string_view space_delimiter{" "};

const auto get_operation = [](const auto &operation_string) {
  auto operands = operation_string | std::views::split(space_delimiter) |
                  std::views::drop(1);
  const auto op_operator = *(operands.begin());
  const auto second_op = *(std::next(operands.begin()));

  const std::string_view myoperator{op_operator.begin(), op_operator.end()};
  const std::string_view second_operand{second_op.begin(), second_op.end()};

  std::function<checked_uint(checked_uint, checked_uint)> operation{};
  if (myoperator == "+") {
    operation = std::plus<>();
  }
  if (myoperator == "*") {
    operation = std::multiplies<>();
  }

  std::size_t operand2{};
  if (second_operand == "old") {
    operand2 = 0;
  } else {
    std::from_chars(second_operand.begin(), second_operand.end(), operand2);
  }

  return [operand2, operation](const checked_uint old) {
    return std::invoke(operation, old, (operand2 == 0 ? old : operand2));
  };
};

const auto get_num_from_string = [](const auto &item) {
  std::size_t number{};
  std::from_chars(item.begin(), item.end(), number);
  return number;
};

const auto get_monkeys = [](const auto &section) {
  auto lines =
      section | std::views::split(line_delimiter) | std::views::drop(1);
  auto items_line = lines.begin();
  auto items =
      *items_line | std::views::split(name_delimiter) | std::views::drop(1);
  auto current_items = items.begin();

  auto monkey_items = *current_items | std::views::split(item_delimiter) |
                      std::views::transform(get_num_from_string);

  auto operation_line = std::next(items_line);

  auto operation = *operation_line | std::views::split(operation_delimiter) |
                   std::views::drop(1) | std::views::transform(get_operation);

  auto divide_by_line = std::next(operation_line);
  const auto number_of_spaces_to_divide_num{5};
  auto divide_by_num = *divide_by_line | std::views::split(space_delimiter) |
                       std::views::drop(number_of_spaces_to_divide_num) |
                       std::views::transform(get_num_from_string);

  auto true_line = std::next(divide_by_line);
  const auto number_of_spaces_to_true_num{9};
  auto true_num = *true_line | std::views::split(space_delimiter) |
                  std::views::drop(number_of_spaces_to_true_num) |
                  std::views::transform(get_num_from_string);

  auto false_line = std::next(true_line);
  const auto number_of_spaces_to_false_num{9};
  auto false_num = *false_line | std::views::split(space_delimiter) |
                   std::views::drop(number_of_spaces_to_false_num) |
                   std::views::transform(get_num_from_string);

  Monkey current_monkey{};
  std::ranges::copy(monkey_items, std::back_inserter(current_monkey.items));
  current_monkey.item_operation = *(operation.begin());
  current_monkey.test = *(divide_by_num.begin());
  current_monkey.true_monkey = *(true_num.begin());
  current_monkey.false_monkey = *(false_num.begin());
  ;

  return current_monkey;
};

const std::size_t num_of_monkeys{8};

const auto print_monkeys = [](const auto &monkeys, const auto &monkey_counter) {
  std::size_t counter{0};
 /* for (const auto &monkey : monkeys) {
    fmt::print("Monkey {} Items => ", counter);
    for (const auto &item : monkey.items) {
      std::cout << item << "|";
    }
  */  fmt::print("\t Transaction Count => {}\n", monkey_counter.at(counter));
    counter++;
  }
};

} // namespace

int main() {
  auto monkeys = inputdata | std::views::split(sectiondelimiter) |
                 std::views::transform(get_monkeys);

  std::array<Monkey, num_of_monkeys> monkey_store{};

  std::array<std::size_t, num_of_monkeys> monkey_move_counter{};

  std::ranges::copy(monkeys, monkey_store.begin());

 // print_monkeys(monkey_store, monkey_move_counter);

  for (const auto index : std::views::iota(1, 10001)) {
    fmt::print("\nAfter Round: {}\n", index);

    std::size_t monkey_index{};
    for (auto &monkey : monkey_store) {
      while (!monkey.items.empty()) {
        auto item = monkey.items.back();
        monkey.items.pop_back();
        item = monkey.item_operation(item);

        if ((item % monkey.test) == 0) {
          monkey_store.at(monkey.true_monkey).items.push_back(item);
        } else {
          monkey_store.at(monkey.false_monkey).items.push_back(item);
        }
        monkey_move_counter.at(monkey_index)++;
      }
            monkey_index++;
    }
    
    print_monkeys(monkey_store, monkey_move_counter);
    fmt::print("\n-------\n");
  }

  std::ranges::sort(monkey_move_counter, std::ranges::greater());

  const auto first = monkey_move_counter.at(0);
  const auto second = monkey_move_counter.at(1);

  fmt::print("Top 2 multiplied =>{} * {} => {}\n", first, second,
             first * second);
}
