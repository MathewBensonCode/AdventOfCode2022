#include "input2.hpp"
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main()
{
  std::istringstream inputstringstream{ inputdata };

    if (!inputstringstream) {
      return 2;
  }

  auto gamescore{ 0U };

    while (!inputstringstream.eof()) {
      auto gameoutcome = std::string{};

      std::getline(inputstringstream, gameoutcome);

        if (gameoutcome.empty()) {
          continue;
      }

      const auto myvalue = gameoutcome[2];

      const auto winning_score{ 6U };
      const auto draw_score{ 3U };

      const auto rock_score{ 1U };
      const auto paper_score{ 2U };
      const auto scissors_score{ 3U };

      const auto losing_score{ 0U };

      const auto mymoves = std::map<const char, const unsigned>{
        { 'X', rock_score }, { 'Y', paper_score }, { 'Z', scissors_score }
      };

      const auto win_lose = std::map<const std::string, const unsigned>{
        // I draw
        { std::string{ "A X" }, draw_score },
        { std::string{ "B Y" }, draw_score },
        { std::string{ "C Z" }, draw_score },

        // I win
        { std::string{ "C X" }, winning_score },
        { std::string{ "A Y" }, winning_score },
        { std::string{ "B Z" }, winning_score },

        // I Lose
        { std::string{ "A Z" }, losing_score },
        { std::string{ "C Y" }, losing_score },
        { std::string{ "B X" }, losing_score }
      };

      const auto roundscore = mymoves.at(myvalue) + win_lose.at(gameoutcome);

      std::cout << "Game: \n input => " << gameoutcome << "\tScore=> "
                << roundscore << '\n';

      gamescore += roundscore;
    }

  std::cout << "Games Total Score => " << gamescore << '\n';
}
