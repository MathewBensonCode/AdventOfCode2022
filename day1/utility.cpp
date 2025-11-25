#include <algorithm>
#include <atomic>
#include <numeric>
#include <utility.hpp>
#include <execution>
#include <vector>

template<typename T>
void scan_tile_state<T>::set_local_prefix(unsigned tile_id, T local_prefix){
    prefixes[tile_id].local_prefix = local.prefix;

    if(tile_id ==0){
        prefixes[tile_id].complete_prefix = local_prefix;
        prefixes[tile_id].state.store(status::complete, std::memory_order_release);
    }
    else{
        prefixes[tile_id].state.store(status::local, std::memory_order_release);
    }
    prefixes[tile_id].state.notify_all();
}

template<typename T>
T scan_tile_state<T>::wait_for_predecessor_prefix(unsigned tile_id){
    T predecessor_prefix{};
    for (std::intptr_t position = tile_id; position >= 0; --position) {
        prefixes[position].state.wait(status::unavailable, std::memory_order_acquire);
        auto state = prefixes[position].state.load(std::memory_order_acquire);

        if(state == status::local){
            predecessor_prefix = prefixes[position].local_prefix + predecessor_prefix;
        }
        else if(state == status::complete){
            predecessor_prefix = prefixes[position].complete_prefix + predecessor_prefix;
            break;
        }
    }

    prefixes[tile_id].complete_prefix = predecessor_prefix + prefixes[tile_id].local;
    prefixes[tile_id].state.store(status::complete, std::memory_order_release);
    prefixes[tile_id].state.notify_all();

    return predecessor_prefix;
}

auto split_parallel_multi_pass(const std::ranges::range auto& input_range, std::ranges::range auto&& output_range, auto &&binary_operation){
    std::vector<interval> intervals(std::size(input_range) + 1);
    
    intervals[0] = {true, 0, 1, 1};
    std::for_each(std::execution::par, std::views::pairwise(intervals), std::begin(intervals) + 1, [&](auto lr) {
            auto [left, right] = lr;
            bool result = binary_operation(left, right); 
            return interval{ result, !result, 1, 1};
            });

    intervals.back() = {false, 0, 1, 1}; 

    std::inclusive_scan(std::execution::par, std::begin(intervals), std::end(intervals), std::begin(intervals));

    std::for_each(std::execution::par, std::views::pairwise(intervals), 
            [&](auto left_right){
                auto [left, right] = left_right;
                if(!right.flag){
                    output_range[left.index] = std::ranges::subrange(std::next(std::begin(input_range), left.end - left.count),
                                                            std::next(std::begin(input_range), left.end));
                }
    });

    return std::ranges::subrange(std::begin(output_range), std::next(std::begin(output_range), intervals.back().index));

}

unsigned read_and_sum_parallel(const auto &input_range, const unsigned number_of_tiles){
    scan_tile_state<std::ranges::range_value_t<decltype(input_range)>> sts(number_of_tiles);
    std::atomic<unsigned> tile_counter(0);
    
    std::for_each(std::views::iota(unsigned{}, number_of_tiles),
            [&] (auto) {

                auto tile = tile_counter.fetch_add(1, std::memory_order_relaxed);

                auto sub_input_range = range_for_tile(input_range, tile, number_of_tiles);

                sts.set_local_prefix(tile, *(--std::inclusive_scan(sub_input_range, std::begin(sub_input_range))));

                if (tile != 0) {
                   auto predecessor = sts.wait_for_predecessor_prefix(tile); 
                   std::ranges::for_each(sub_input_range, [&] (auto &element) { element = predecessor + element; });
                }

            });

}

interval operator+(const interval left, const interval right){
  return {
    right.flag,
    left.index + right.index,
    right.index? right.count : left.count + right.count,
    left.end + right.end
  };
}

auto split_parallel_parallel(const std::ranges::range auto &input_range, std::ranges::range auto &output_range, std::predicate auto&&binary_operation, const unsigned tile_count){
    scan_tile_state<interval> scantilestate(tile_count);
    std::atomic<unsigned> tile_counter(0);
    
    std::for_each(std::execution::par, std::views::iota(unsigned{}, tile_count),
            [&](auto){
            auto tile = tile_counter.fetch_add(1, std::memory_order::relaxed);
            bool is_first_tile = tile == 0;
            bool is_last_tile = tile == tile_count -1;
            bool is_interior_tile = (!is_first_tile && !is_last_tile);

            auto sub_input_range = range_for_tile(input_range, tile, tile_count);

            if(!is_first_tile){
                sub_input_range = std::ranges::subrange(--std::begin(sub_input_range), std::end(sub_input_range));
            }

            std::vector<interval> intervals(std::size(sub_input_range) - is_interior_tile);
               
            if(is_first_tile){
                intervals[tile] = {true, 0, 1, 1};
            }
            std::transform(std::execution::par, std::views::pairwise(sub_input_range), std::begin(sub_input_range) + is_first_tile, 
                    [&](auto left_right){
                        auto [left, right] = left_right;
                        bool flag = binary_operation(left, right);
                        return interval{flag, !flag, 1, 1};
                    });
                    
            if(is_last_tile){
                intervals.back() = {false, 1, 1, 1};
            }

            scantilestate.set_local_prefix(tile, *(--std::inclusive_scan(std::execution::par, std::begin(intervals), std::end(intervals), std::begin(intervals))));

            if(!is_first_tile) {
                auto predecessor_prefix = scantilestate.wait_for_predecessor_prefix(tile);
                std::for_each(std::begin(intervals), std::end(intervals), [&] (auto& current){
                            current = predecessor_prefix + current;
                        });
            }

            std::ranges::for_each(intervals | std::views::pairwise, [&](auto left_right){
                auto [left, right] = left_right;
                if (!right.flag){
                
                    output_range[left.index] = std::ranges::subrange(std::next(std::begin(input_range), left.end - left.count), std::next(std::begin(input_range), left.end));
                }
            });
            

            });

}
