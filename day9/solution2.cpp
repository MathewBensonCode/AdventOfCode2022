#include "input9.hpp"
import std;

namespace {

struct point {
  unsigned x;
  unsigned y;
};

enum class direction {
  none,
  up,
  down,
  left,
  right,
  up_left,
  up_right,
  down_left,
  down_right
};

direction operator-(const point &head, const point &tail) {
  int x_difference = static_cast<int>(head.x) - static_cast<int>(tail.x);
  int y_difference = static_cast<int>(head.y) - static_cast<int>(tail.y);

  if (y_difference == 0) {
    if (x_difference < -1) {
      return direction::left;
    }

    if (x_difference > 1) {
      return direction::right;
    }
  }

  if (x_difference == 0) {
    if (y_difference < -1) {
      return direction::down;
    }

    if (y_difference > 1) {
      return direction::up;
    }
  }

  if ((x_difference > 1 && y_difference >= 1) ||
      (x_difference >= 1 && y_difference > 1)) {
    return direction::up_right;
  }

  if ((x_difference < -1 && y_difference >= 1) ||
      (x_difference <= -1 && y_difference > 1)) {
    return direction::up_left;
  }

  if ((x_difference >= 1 && y_difference < -1) ||
      (x_difference > 1 && y_difference <= -1)) {
    return direction::down_right;
  }
  if ((x_difference <= -1 && y_difference < -1) ||
      (x_difference < -1 && y_difference <= -1)) {
    return direction::down_left;
  }

  return direction::none;
}
} // namespace

int main() {
  std::string_view inputstringview{inputdata};
  constexpr auto number_of_input_lines{2000};
  auto data_view = inputstringview | std::views::split('\n') |
                   std::views::drop(1) |
                   std::views::take(number_of_input_lines);
  constexpr std::size_t grid_width{600};
  const auto center_point{grid_width / 2};
  const point starting_point{center_point, center_point};

  std::array<std::array<short, grid_width>, grid_width> tail_counter{};
  tail_counter.at(center_point).at(center_point)++;

  point head{starting_point};
  constexpr std::size_t tail_length{9};
  std::array<point, tail_length> tails{};
  tails.fill(starting_point);

  auto move_up = [](point &point) { point.y++; };

  auto move_down = [](point &point) { point.y--; };

  auto move_left = [](point &point) { point.x--; };

  auto move_right = [](point &point) { point.x++; };

  auto move_up_left = [&](point &point) {
    move_up(point);
    move_left(point);
  };

  auto move_up_right = [&](point &point) {
    move_up(point);
    move_right(point);
  };

  auto move_down_left = [&](point &point) {
    move_down(point);
    move_left(point);
  };

  auto move_down_right = [&](point &point) {
    move_down(point);
    move_right(point);
  };

  auto move_tail = [&](point &first, point &second) {
    direction second_direction = first - second;

    switch (second_direction) {
    case direction::left: {
      move_left(second);
      break;
    }
    case direction::right: {
      move_right(second);
      break;
    }
    case direction::none: {
      break;
    }
    case direction::up: {
      move_up(second);
      break;
    }
    case direction::down: {
      move_down(second);
      break;
    }
    case direction::up_left: {
      move_up_left(second);
      break;
    }
    case direction::up_right: {
      move_up_right(second);
      break;
    }
    case direction::down_left: {
      move_down_left(second);
      break;
    }
    case direction::down_right: {
      move_down_right(second);
      break;
    }
    }
  };

  auto move_head = [&](const char direction, const std::size_t moves) {
    std::string_view direction_string{};
    if (direction == 'D') {
      direction_string = "Down";
    }

    if (direction == 'U') {
      direction_string = "Up";
    }

    if (direction == 'L') {
      direction_string = "Left";
    }

    if (direction == 'R') {
      direction_string = "Right";
    }

    std::print("---\nMove Head in {} direction {} times\n", direction_string,
               moves);

    for (std::size_t index{}; index < moves; ++index) {
      if (direction == 'U') {
        move_up(head);
      }
      if (direction == 'D') {
        move_down(head);
      }
      if (direction == 'L') {
        move_left(head);
      }
      if (direction == 'R') {
        move_right(head);
      }

      std::print("HEAD at x={}, y={}\n", head.x, head.y);

      point &initial_point = tails.at(0);
      move_tail(head, initial_point);

      std::print("\tKnot {} at x={},y={}\n", 1, initial_point.x,
                 initial_point.y);

      for (std::size_t tail_index{}; tail_index < tail_length - 1;
           ++tail_index) {
        auto &previous_point = tails.at(tail_index);
        auto &current_point = tails.at(tail_index + 1);
        move_tail(previous_point, current_point);
        std::print("\tKnot {} at x={},y={}\n", tail_index + 2, current_point.x,
                   current_point.y);
      }

      tail_counter.at(tails.at(tail_length - 1).y)
          .at(tails.at(tail_length - 1).x)++;
    }
  };

  for (auto line : data_view) {
    std::string linestring(line.begin(), line.end());
    std::stringstream linestream{linestring};
    char direction{};
    linestream >> direction;
    std::size_t moves{};
    linestream >> moves;

    move_head(direction, moves);
  }

  std::size_t tail_location_count{};
  for (auto &line : tail_counter) {
    for (auto &location : line) {
      if (location > 0) {
        tail_location_count++;
        continue;
      }
    }
  }

  std::print("Total Locations visited by tail = {} \n", tail_location_count);
}
