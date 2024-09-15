export module module8;
import std;

export namespace day8 {
const std::size_t array_width{99};
constexpr std::string_view delim{"\n"};

void print_current(const auto& current) { std::print(" => {} -> ", current); };
} // namespace day8
