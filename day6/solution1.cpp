import input6;
import std;

int main() {
  constexpr auto width{4};

  constexpr std::string_view inputdatastring(inputdata);

  for (std::size_t index{}; index < inputdatastring.length() - width; ++index) {

    auto endlocation = width + index;
    auto vals = inputdatastring | std::ranges::views::drop(index) |
                std::ranges::views::take(width);

    std::string_view store(std::begin(vals), std::end(vals));

    std::print("{}\t{}\n", store, endlocation);

    std::size_t not_unique{};
    for (const auto &val : store) {
      if (store.find(val) != store.rfind(val)) {
        not_unique++;
      }
    }

    if (not_unique == 0) {
      std::print("\t\tFound It\n");
      break;
    }
  }
}
