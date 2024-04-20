#include "input2.hpp"

import std;

using namespace std::literals::string_view_literals;

namespace {
constexpr auto line_delimiter{"\n"sv};

const auto winning_score{6};
const auto draw_score{3};
const auto lose_score{0};

const auto rock_score{1};
const auto paper_score{2};
const auto scissors_score{3};

const auto win_draw_lose = [](char move) {
  if (move == 'Z') {
    return winning_score;
  }
  if (move == 'Y') {
    return draw_score;
  }
  if (move == 'X') {
    return lose_score;
  }
  return 0;
};

const auto moves = [](std::string_view game) {
  if (game == "A Z"sv || game == "B Y"sv || game == "C X"sv) {
    return paper_score;
  }

  if (game == "B Z"sv || game == "C Y"sv || game == "A X"sv) {
    return scissors_score;
  }

  if (game == "C Z"sv || game == "A Y"sv || game == "B X"sv) {
    return rock_score;
  }

  return 0;
};

const auto get_game_score = [](const auto &game) {
  std::string_view gameoutcome{game.begin(), game.end()};

  auto roundscore{0};

  const auto myvalue = gameoutcome.back();

  roundscore += win_draw_lose(myvalue) + moves(gameoutcome);

  std::print("Game => {} | Score => {} \n", gameoutcome, roundscore);

  return roundscore;
};

} // namespace

int main() {

  auto games = std::string_view{inputdata} | std::views::split(line_delimiter) |
               std::views::transform(get_game_score) | std::views::common;

  const auto gamescore{std::accumulate(games.begin(), games.end(), 0)};

  std::print("Games Total Score => {}\n", gamescore);
}
