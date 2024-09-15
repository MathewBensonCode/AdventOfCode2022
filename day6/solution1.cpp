import input6;
import std;

int main() {
  try {
    const auto width{4};

  constexpr std::string_view inputdatastring(inputdata);

  for (std::size_t index{}; index < inputdatastring.length() - width; ++index) {

      auto endlocation = width + index;
      auto vals = inputdatastring | std::ranges::views::drop(index) |
                  std::ranges::views::take(width);

    const std::string_view inputdatastring(inputdata);

      std::print("{}\t{}\n", store, endlocation);

      if (not_unique == 0) {
        std::print("\t\tFound It\n");
        break;
      }

    if (not_unique == 0) {
      std::print("\t\tFound It\n");
      break;
    }
  } catch (std::exception &e) {
  }
}
