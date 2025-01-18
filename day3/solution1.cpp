import module3;
import std;
import input3;

namespace
{
using namespace day3;

const auto get_char_count = [](const auto &line) {
  std::string_view lineinput{ line.begin(), line.end() };
  std::size_t count{};

  auto halflength = lineinput.size() / 2;

  std::array<std::size_t, compartment_size> first_compartment{};
  std::array<std::size_t, compartment_size> second_compartment{};

  auto first_half = lineinput.substr(0, halflength);
  auto second_half = lineinput.substr(halflength);

  std::print("Line input : {}\n\n", lineinput);
  std::print("First_Half => {}\n", first_half);
  std::print("Second_Half => {}\n", second_half);

    for (std::size_t index = 0; index < halflength; ++index) {
      const auto first_half_char_index = calculate_letter_index(
        static_cast<unsigned char>(first_half.at(index)));
      const auto second_half_char_index = calculate_letter_index(
        static_cast<unsigned char>(second_half.at(index)));

      first_compartment.at(first_half_char_index)++;
      second_compartment.at(second_half_char_index)++;
    }

    for (std::size_t index = 1; index < compartment_size; ++index) {
        if (first_compartment.at(index) > 0 && second_compartment.at(index) > 0) {
          count += index;
          std::print("Found character : {}\tWith Count : {} \n",
            (calculate_char(index)),
            index);
      }
    }

  return count;
};

}// namespace

int main()
{
    try {
      auto lines = inputdata | std::views::split(line_delimiter) | std::views::transform(get_char_count) | std::views::common;

      const auto final_count =
        std::accumulate(lines.begin(), lines.end(), std::size_t{});

      std::print("Final Count = {}\n", final_count);
    } catch (std::exception &e) {
      std::cerr << "Exception : " << e.what() << '\n';
  }
}
