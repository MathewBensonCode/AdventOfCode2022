export module module4;

import std;

using namespace std::literals::string_view_literals;

export namespace day4 {

constexpr auto line_delimiter{"\n"sv};
constexpr auto pair_delimiter{","sv};
constexpr auto num_delimiter{"-"sv};

struct getpair {
  auto operator()(const auto &pair) {
    auto numbers =
        pair | std::views::split(num_delimiter) |
        std::views::transform([](const auto &num) {
          std::string_view num_string{num.begin(), num.end()};
          int number{};
          std::from_chars(num_string.data(),
                          num_string.data() + num_string.size(), number);
          return number;
        });

    const auto first = std::ranges::begin(numbers);
    const auto second = std::next(first);

    return std::make_pair(*first, *second);
  }
};
} // namespace day4
