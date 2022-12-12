#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main() {
  std::ifstream input{"input"};

  if (!input)
    return 2;

  unsigned int gamescore{};

  while (!input.eof()) {
    std::string gameoutcome{};

    unsigned int roundscore{};

    std::getline(input, gameoutcome);

    if(gameoutcome.length() == 0){
        continue;
    }

    auto gameoutcomedata = gameoutcome.data();

    char myvalue = gameoutcomedata[2];

    std::map<char, unsigned int> win_draw_lose = { {'Z', 6}, {'Y', 3} , { 'X', 0 } };

    std::map<std::string, unsigned int> moves = {
        //Win Moves
        {"A Z", 2},
        {"B Z", 3},
        {"C Z", 1},

        //Draw Moves
        {"A Y", 1},
        {"B Y", 2},
        {"C Y", 3},

        //Lose Moves
        {"A X", 3},
        {"B X", 1},
        {"C X", 2}
    };

    roundscore += win_draw_lose[myvalue];
    roundscore += moves[gameoutcome];

    std::cout<<"Game: \n input => "<<gameoutcome<<"\tScore=> "<<roundscore<<'\n';

    gamescore += roundscore;
  }

  std::cout<<"Games Total Score => "<< gamescore<<'\n';
}
