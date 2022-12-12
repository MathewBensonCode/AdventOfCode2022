#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main() {
  std::ifstream input{"input.txt"};

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

    std::map<char, unsigned int> mymoves = { {'X', 1}, {'Y', 2} , { 'Z', 3 } };

    std::map<std::string, unsigned int> win_lose = {
        //Same Moves
        {"A X", 3},
        {"B Y", 3},
        {"C Z", 3},

        //I win
        {"C X", 6},
        {"A Y", 6},
        {"B Z", 6}
    };

    roundscore += mymoves[myvalue];
    roundscore += win_lose[gameoutcome];

    std::cout<<"Game: \n input => "<<gameoutcome<<"\tScore=> "<<roundscore<<'\n';

    gamescore += roundscore;
  }

  std::cout<<"Games Total Score => "<< gamescore<<'\n';
}
