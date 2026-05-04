#include <algorithm>
#include <atomic>
#include <numeric>
#include <utility.hpp>
#include <vector>

namespace utility
{

auto range_for_tile(const auto &input_range, const tile_info info)
{
  auto tile_size = (std::size(input_range) + info.total_number_of_tiles + 1) / info.total_number_of_tiles;
  auto start = std::min(info.tile * tile_size, std::size(input_range));
  auto end = std::min((info.tile + 1) * tile_size, std::size(input_range));

  return std::ranges::subrange(std::next(std::begin(input_range), start), std::next(std::begin(input_range), end));
}

template<typename T>
void scan_tile_state<T>::set_local_prefix(unsigned tile_id, T local_prefix)
{
  prefixes[tile_id].local_prefix = status::local.prefix;

    if (tile_id == 0) {
      prefixes[tile_id].complete_prefix = local_prefix;
      prefixes[tile_id].state.store(status::complete, std::memory_order_release);
    } else {
      prefixes[tile_id].state.store(status::local, std::memory_order_release);
    }
  prefixes[tile_id].state.notify_all();
}

template<typename T>
T scan_tile_state<T>::wait_for_predecessor_prefix(unsigned tile_id)
{
  T predecessor_prefix{};
    for (std::intptr_t position = tile_id; position >= 0; --position) {
      prefixes[position].state.wait(status::unavailable, std::memory_order_acquire);
      auto state = prefixes[position].state.load(std::memory_order_acquire);

        if (state == status::local) {
          predecessor_prefix = prefixes[position].local_prefix + predecessor_prefix;
        } else if (state == status::complete) {
          predecessor_prefix = prefixes[position].complete_prefix + predecessor_prefix;
          break;
      }
    }

  prefixes[tile_id].complete_prefix = predecessor_prefix + prefixes[tile_id].local;
  prefixes[tile_id].state.store(status::complete, std::memory_order_release);
  prefixes[tile_id].state.notify_all();

  return predecessor_prefix;
}

unsigned read_and_sum_parallel(const auto &input_range, const unsigned number_of_tiles)
{
  scan_tile_state<std::ranges::range_value_t<decltype(input_range)>> sts(number_of_tiles);
  std::atomic<unsigned> tile_counter(0);

  std::for_each(std::views::iota(unsigned{}, number_of_tiles),
    [&](auto) {
      auto tile = tile_counter.fetch_add(1, std::memory_order_relaxed);

      auto sub_input_range = range_for_tile(input_range, tile, number_of_tiles);

      sts.set_local_prefix(tile, *(--std::inclusive_scan(sub_input_range, std::begin(sub_input_range))));

        if (tile != 0) {
          auto predecessor = sts.wait_for_predecessor_prefix(tile);
          std::ranges::for_each(sub_input_range, [&](auto &element) { element = predecessor + element; });
      }
    });
  return input_range.back();
}

interval interval::operator+(const interval &right)
{
  auto &left = *this;

  return {
    .flag = right.flag,
    .index = left.index + right.index,
    .count = (right.index != 0U) ? right.count : left.count + right.count,
    .end = left.end + right.end
  };
}

}// namespace utility
