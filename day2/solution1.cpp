#include "input2.hpp"
#include <iostream>
#include <map>
#include <numeric>
#include <string>

namespace{
    const auto winning_score{6};
    const auto draw_score{3};

    const auto rock_score{1};
    const auto paper_score{2};
    const auto scissors_score{3};
}

int main() {
    
  std::string_view inputstring{inputdata};

  std::vector<unsigned> gamescores{};

  for (auto counter_iterator = std::begin(inputstring), end_iterator = std::end(inputstring);
          counter_iterator != end_iterator;) {

    unsigned roundscore{};

    auto end_of_line = std::find(counter_iterator, end_iterator, '\n');

    std::string_view gameoutcome{counter_iterator, end_of_line};

    char myvalue = gameoutcome.back();

    std::map<char, std::size_t> mymoves = {
        {'X', rock_score}, {'Y', paper_score}, {'Z', scissors_score}};

    std::map<std::string_view, std::size_t> win_lose = {// Same Moves
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

    gamescores.push_back(roundscore);

    counter_iterator = (end_of_line != end_iterator)? std::next(end_of_line, 1) : end_of_line;
    
  }

  std::cout << "Games Total Score => " << std::reduce(std::begin(gamescores), std::end(gamescores), unsigned{})<< '\n';
}
