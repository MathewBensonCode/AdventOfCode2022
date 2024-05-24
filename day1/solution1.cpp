import day1lib;
import std;

using namespace day1;

int main() {
    auto sections = input_string | std::views::split(section_delimiter) |
                    std::views::transform(get_section_sum{});

    const auto count = *(std::ranges::max_element(sections));

    std::print("Highest Element = {}\n ", count);

};
