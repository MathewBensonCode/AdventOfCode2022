#include "input9.hpp"
import std;

namespace {
struct point {
  std::size_t x;
  std::size_t y;
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

  if ((x_difference > 1 && y_difference == 1) ||
      (x_difference == 1 && y_difference > 1)) {
    return direction::up_right;
  }

  if ((x_difference < -1 && y_difference == 1) ||
      (x_difference == -1 && y_difference > 1)) {
    return direction::up_left;
  }

  if ((x_difference == 1 && y_difference < -1) ||
      (x_difference > 1 && y_difference == -1)) {
    return direction::down_right;
  }
  if ((x_difference == -1 && y_difference < -1) ||
      (x_difference < -1 && y_difference == -1)) {
    return direction::down_left;
  }

  return direction::none;
}
} // namespace
int main() {
  std::string_view inputstringview{inputdata};
  const auto number_of_input_lines{2000};
  auto data_view = inputstringview | std::views::all | std::views::split('\n') |
                   std::views::drop(1) |
                   std::views::take(number_of_input_lines);
  const std::size_t grid_width{600};
  const auto center_point{grid_width / 2};
  const point starting_point{center_point, center_point};

  std::array<std::array<short, grid_width>, grid_width> tail_counter{};

  tail_counter.at(center_point).at(center_point)++;

  point head{starting_point};
  point tail{starting_point};

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

  auto move_tail = [&] {
    direction tail_direction = head - tail;

    switch (tail_direction) {
    case direction::left: {
      move_left(tail);
      std::print("moved left\n");
      break;
    }
    case direction::right: {
      move_right(tail);
      std::print("moved right\n");
      break;
    }
    case direction::none: {
      std::print("no move\n");
      break;
    }
    case direction::up: {
      move_up(tail);
      std::print("moved up\n");
      break;
    }
    case direction::down: {
      move_down(tail);
      std::print("moved down\n");
      break;
    }
    case direction::up_left: {
      move_up_left(tail);
      std::print("moved up_and_left\n");
      break;
    }
    case direction::up_right: {
      move_up_right(tail);
      std::print("moved up_and_right\n");
      break;
    }
    case direction::down_left: {
      move_down_left(tail);
      std::print("moved down_and_left\n");
      break;
    }
    case direction::down_right: {
      move_down_right(tail);
      std::print("moved down_and_right\n");
      break;
    }
    }
    std::print("Tail point at x={}, y={} | Head point at x={}, y={}\n", tail.x,
               tail.y, head.x, head.y);
    tail_counter.at(tail.y).at(tail.x)++;
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

    std::print("\n----\nmove Head in {} direction ->  {} times\n",
               direction_string, moves);

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
      move_tail();
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
  std::print("Tail Locations\n");
  for (const auto &line : tail_counter) {
    for (const auto &location : line) {
      if (location > 0) {
        tail_location_count++;
        continue;
      }
    }
  }

  std::print("Total Locations visited by tail = {} \n", tail_location_count);
}
