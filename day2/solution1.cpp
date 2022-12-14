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

    std::size_t roundscore{};

    std::getline(inputstringstream, gameoutcome);

    if (gameoutcome.length() == 0) {
      continue;
    }

    char myvalue = gameoutcome[2];

    const auto winning_score{6};
    const auto draw_score{3};

    const auto rock_score{1};
    const auto paper_score{2};
    const auto scissors_score{3};

    std::map<char, std::size_t> mymoves = {
        {'X', rock_score}, {'Y', paper_score}, {'Z', scissors_score}};

    std::map<std::string, std::size_t> win_lose = {// Same Moves
                                                   {"A X", draw_score},
                                                   {"B Y", draw_score},
                                                   {"C Z", draw_score},

                                                   // I win
                                                   {"C X", winning_score},
                                                   {"A Y", winning_score},
                                                   {"B Z", winning_score}};

    roundscore += mymoves[myvalue];
    roundscore += win_lose[gameoutcome];

    std::cout << "Game: \n input => " << gameoutcome << "\tScore=> "
              << roundscore << '\n';

    gamescore += roundscore;
  }

  std::cout << "Games Total Score => " << gamescore << '\n';
}
