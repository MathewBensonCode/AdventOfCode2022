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

  std::size_t gamescore{};

  while (!inputstringstream.eof()) {
    std::string gameoutcome{};

    std::getline(inputstringstream, gameoutcome);

    std::size_t roundscore{};

    if (gameoutcome.length() == 0) {
      continue;
    }

    char myvalue = gameoutcome[2];

    const auto winning_score{6};
    const auto draw_score{3};
    const auto lose_score{0};

    std::map<char, std::size_t> win_draw_lose = {
        {'Z', winning_score}, {'Y', draw_score}, {'X', lose_score}};

    const auto rock_score{1};
    const auto paper_score{2};
    const auto scissors_score{3};

    std::map<std::string, std::size_t> moves = {// Win Moves
                                                {"A Z", paper_score},
                                                {"B Z", scissors_score},
                                                {"C Z", rock_score},

                                                // Draw Moves
                                                {"A Y", rock_score},
                                                {"B Y", paper_score},
                                                {"C Y", scissors_score},

                                                // Lose Moves
                                                {"A X", scissors_score},
                                                {"B X", rock_score},
                                                {"C X", paper_score}};

    roundscore += win_draw_lose[myvalue];
    roundscore += moves[gameoutcome];

    std::cout << "Game: \n input => " << gameoutcome << "\tScore=> "
              << roundscore << '\n';

    gamescore += roundscore;
  }

  std::cout << "Games Total Score => " << gamescore << '\n';
}
