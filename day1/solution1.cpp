#include "input1.hpp"
#include "utility.hpp"

int main() {

    std::string_view inputstring{inputdata};
    const unsigned tiles = 8;

    std::vector<char> output(std::size(inputstring));

     auto result = split_parallel_multi_pass(inputstring, output, [](const auto first, auto){
                return (!first == '\n');
                });

}
