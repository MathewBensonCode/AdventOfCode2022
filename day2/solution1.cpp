#include "input2.hpp"
#include <numeric>
#include <ranges>
#include <string_view>

import fmt;

using namespace std::literals::string_view_literals;

namespace {
constexpr auto line_delimiter{"\n"sv};
constexpr auto winning_score{6};
constexpr auto draw_score{3};
constexpr auto lose_score{0};

constexpr auto rock_score{1};
constexpr auto paper_score{2};
constexpr auto scissors_score{3};

const auto mymoves = [](char move) {
  if (move == 'X') {
    return rock_score;
  }
  if (move == 'Y') {
    return paper_score;
  }
  if (move == 'Z') {
    return scissors_score;
  }
  return 0;
};

const auto win_lose = [](std::string_view game) {
  if (game == "A X"sv || game == "B Y"sv || game == "C Z"sv) {
    return draw_score;
  }
  if (game == "C X"sv || game == "A Y"sv || game == "B Z"sv) {
    return winning_score;
  }

  return lose_score;
};

const auto get_game_score = [](const auto &game) {
  const std::string_view gameoutcome{game.begin(), game.end()};
  auto roundscore{0};

  char myvalue = gameoutcome.back();

  roundscore += mymoves(myvalue);
  roundscore += win_lose(gameoutcome);

  fmt::print("Game => {} | Score => {}\n", gameoutcome, roundscore);

  return roundscore;
};

} // namespace

int main() {
  auto games = std::string_view{inputdata} | std::views::split(line_delimiter) |
               std::views::transform(get_game_score) | std::views::common;

  auto gamescore = std::accumulate(games.begin(), games.end(), 0);
  fmt::print("Games Total Score => {}\n", gamescore);
}
