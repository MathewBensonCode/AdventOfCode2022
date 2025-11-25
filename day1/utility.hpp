#include <atomic>
#include <vector>
#include <ranges>

auto ranges_for_tile(std::ranges::range auto &&input_range,
  std::size_t tile,
  std::size_t num_tiles)
{
  auto tile_size = (std::size(input_range) + num_tiles + 1) / num_tiles;
  auto start = std::min(tile * tile_size, std::size(input_range));
  auto end = std::min((tile + 1) * tile_size, std::size(input_range));

  return std::ranges::subrange(std::next(std::begin(input_range), start), std::next(std::begin(input_range), end));
}

template<typename T>
class scan_tile_state
{
  enum status {
    unavailable,
    local,
    complete
  };

  struct Descriptor
  {
    T local_prefix = {};
    T complete_prefix = {};
    std::atomic<status> state = status::unavailable;
  };

  std::vector<Descriptor> prefixes;

public:
  explicit scan_tile_state(std::size_t tile_id) : prefixes(tile_id)
  {
  }

  void set_local_prefix(const unsigned, const T);

  T wait_for_predecessor_prefix(const unsigned);
};

unsigned read_and_sum_parallel(const auto &input_range, const unsigned number_of_tiles);

struct interval{
    bool flag = true;
    unsigned index = 0; //plus scan of inverse flags
    unsigned count = 0; //counts elements with the same index(current index)
    unsigned end = 0; //counts all elements
};

interval operator+(const interval, const interval);

auto split_parallel_multi_pass(const auto & /*input_range*/, auto &/*output_range*/, auto&& /*binary_predicate*/); 
auto split_parallel_parallel(const std::ranges::range auto &, std::ranges::range auto &, std::predicate auto&&, const unsigned); 
