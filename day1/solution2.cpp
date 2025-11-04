#include "input1.hpp"
#include <iostream>
#include <numeric>
#include <vector>
#include <iterator>

namespace{
auto get_string_as_number = [] (auto &begin_iterator, const auto &end_iterator){

    std::string number_string{begin_iterator, end_iterator};

    unsigned number = static_cast<unsigned>(stoul(number_string));

    begin_iterator = end_iterator;

    return number;
};

auto get_section_sum = [](auto &begin_iterator, const auto &end_iterator){

    std::vector<unsigned> numbers;
   
    while(begin_iterator != end_iterator){
        auto end_of_line = std::find(begin_iterator, end_iterator, '\n');

        numbers.push_back(get_string_as_number(begin_iterator, end_of_line));

        if(end_of_line != end_iterator){
            begin_iterator = std::next(end_of_line);
        }
       
    }

    return std::accumulate(std::begin(numbers), std::end(numbers), unsigned{});
};
}

int main() {

    std::string_view inputdata{inputstring};
    auto counter = std::begin(inputdata);
    auto endpoint = std::end(inputdata);

    std::vector<unsigned> sums{};

    while(counter != endpoint){
        auto end_of_section = std::adjacent_find(counter, endpoint, [](auto first, auto second){
                    return (first == '\n' && second == '\n');
                });
    
        sums.push_back(get_section_sum(counter, end_of_section));

        if(end_of_section != endpoint){
            counter = std::next(end_of_section, 2);
        }

    }

    std::sort(std::begin(sums), std::end(sums), std::greater<unsigned>{});

    std::vector<unsigned> highest_three(3);

    std::copy_n(std::begin(sums), highest_three.size(), std::begin(highest_three));

    unsigned sum_of_highest_three = std::accumulate(std::begin(highest_three), std::end(highest_three), unsigned{});

    std::cout<<"Highest Three Sections => \n";

    for(auto element : highest_three){
        std::cout << element << '\n';
    }

    std::cout<< "With Sum => " << sum_of_highest_three;

}
