#include <string_view>

namespace day3{
const auto compartment_size{53};
const auto small_letter_offset{96};
const auto capital_letter_offset{38};
const auto small_capital_boundary{27};

constexpr std::string_view line_delimiter{"\n"};

const auto calculate_letter_index = [](unsigned char letter) {
  auto value = static_cast<std::size_t>(letter);

  if (value > small_letter_offset) {
    return value - small_letter_offset;
  }
  return value - capital_letter_offset;
};

const auto calculate_char = [](std::size_t value) {
  if (value < small_capital_boundary) {
    return static_cast<char>(value + small_letter_offset);
  }
  return static_cast<char>(value + capital_letter_offset);
};

} // namespace
