#include <atomic>
#include <execution>
#include <vector>
#include <ranges>

namespace utility
{

struct tile_info
{
  unsigned tile{};
  unsigned total_number_of_tiles{};
};

auto range_for_tile(const auto &input_range,
  tile_info);

template<typename T>
class scan_tile_state
{
  enum class status : char {
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

  void set_local_prefix(unsigned, T);

  T wait_for_predecessor_prefix(unsigned);
};

unsigned read_and_sum_parallel(const auto &input_range, unsigned number_of_tiles);

struct interval
{
  bool flag = true;
  unsigned index = 0;// plus scan of inverse flags
  unsigned count = 0;// counts elements with the same index(current index)
  unsigned end = 0;// counts all elements

  interval operator+(const interval &);
};


inline void split_parallel_multi_pass(std::string_view input_range, std::vector<char> &output_range, auto &&binary_predicate)
{
  std::vector<interval> intervals(std::size(input_range) + 1);

  intervals[0] = { .flag = true, .index = 0, .count = 1, .end = 1 };
  std::for_each(std::execution::par, std::views::pairwise(intervals), std::begin(intervals) + 1, [&](auto left_right) {
    auto [left, right] = left_right;
    bool result = binary_predicate(left, right);
    return interval{ .flag = result, .index = !result, .count = 1, .end = 1 };
  });

  intervals.back() = { .flag = false, .index = 0, .count = 1, .end = 1 };

  std::inclusive_scan(std::execution::par, std::begin(intervals), std::end(intervals), std::begin(intervals));

  std::for_each(std::execution::par, std::views::pairwise(intervals), [&](auto left_right) {
    auto [left, right] = left_right;
      if (!right.flag) {
        output_range[left.index] = std::ranges::subrange(std::next(std::begin(input_range), left.end - left.count),
          std::next(std::begin(input_range), left.end));
    }
  });
}

inline auto split_parallel(const std::ranges::range auto &input_range, std::ranges::range auto &output_range, std::predicate auto &&binary_operation, const unsigned tile_count)
{
  scan_tile_state<interval> scantilestate(tile_count);
  std::atomic<unsigned> tile_counter(0);

  std::for_each(std::execution::par, std::views::iota(unsigned{}, tile_count), [&](auto) {
    auto tile = tile_counter.fetch_add(1, std::memory_order::relaxed);
    bool is_first_tile = tile == 0;
    bool is_last_tile = tile == tile_count - 1;
    bool is_interior_tile = (!is_first_tile && !is_last_tile);

    auto sub_input_range = range_for_tile(input_range, tile, tile_count);

      if (!is_first_tile) {
        sub_input_range = std::ranges::subrange(--std::begin(sub_input_range), std::end(sub_input_range));
    }

    std::vector<interval> intervals(std::size(sub_input_range) - is_interior_tile);

      if (is_first_tile) {
        intervals[tile] = { .flag = true, .index = 0, .count = 1, .end = 1 };
    }
    std::transform(std::execution::par, std::views::pairwise(sub_input_range), std::begin(sub_input_range) + is_first_tile, [&](auto left_right) {
      auto [left, right] = left_right;
      bool flag = binary_operation(left, right);
      return interval{ .flag = flag, .index = !flag, .count = 1, .end = 1 };
    });

      if (is_last_tile) {
        intervals.back() = { .flag = false, .index = 1, .count = 1, .end = 1 };
    }

    scantilestate.set_local_prefix(tile, *(--std::inclusive_scan(std::execution::par, std::begin(intervals), std::end(intervals), std::begin(intervals))));

      if (!is_first_tile) {
        auto predecessor_prefix = scantilestate.wait_for_predecessor_prefix(tile);
        std::for_each(std::begin(intervals), std::end(intervals), [&](auto &current) {
          current = predecessor_prefix + current;
        });
    }

    std::ranges::for_each(intervals | std::views::pairwise, [&](auto left_right) {
      auto [left, right] = left_right;
        if (!right.flag) {

          output_range[left.index] = std::ranges::subrange(std::next(std::begin(input_range), left.end - left.count), std::next(std::begin(input_range), left.end));
      }
    });
  });
}

}// namespace utility
