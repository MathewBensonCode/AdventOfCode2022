export module module7;
import std;

export namespace day7 {
struct file {
  std::string name;
  std::size_t size{};
};

struct directory : public file {
  std::weak_ptr<directory> parent;
  std::vector<std::shared_ptr<file>> contents;
};

std::size_t operator+(const std::size_t value1,
                      const std::shared_ptr<file> &other) {
  return value1 + other->size;
}

const std::string_view line_delimiter{"\n"};
} // namespace day7
