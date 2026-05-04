#include "input2.hpp"
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main() {
  std::stringstream inputstringstream{inputdata};

  if (!inputstringstream) {
    return 2;
  }

  auto gamescore{0U};

  while (!inputstringstream.eof()) {
    std::string gameoutcome{};

    std::getline(inputstringstream, gameoutcome);


    if (gameoutcome.empty()) {
      continue;
    }

    const auto myvalue = gameoutcome[2];

    const auto winning_score{6U};
    const auto draw_score{3U};
    const auto lose_score{0U};

    std::map<char, unsigned> win_draw_lose = {
        {'Z', winning_score}, {'Y', draw_score}, {'X', lose_score}};

    const auto rock_score{1U};
    const auto paper_score{2U};
    const auto scissors_score{3U};

    const auto moves = std::map<std::string, unsigned>{// Win Moves
                                                {std::string{"A Z"}, paper_score},
                                                {std::string{"B Z"}, scissors_score},
                                                {std::string{"C Z"}, rock_score},

                                                // Draw Moves
                                                {std::string{"A Y"}, rock_score},
                                                {std::string{"B Y"}, paper_score},
                                                {std::string{"C Y"}, scissors_score},

                                                // Lose Moves
                                                {std::string{"A X"}, scissors_score},
                                                {std::string{"B X"}, rock_score},
                                                {std::string{"C X"}, paper_score}};

    const auto roundscore = win_draw_lose.at(myvalue) + moves.at(gameoutcome);

    std::cout << "Game: \n input => " << gameoutcome << "\tScore=> "
              << roundscore << '\n';

    gamescore += roundscore;
  }

  std::cout << "Games Total Score => " << gamescore << '\n';
}
