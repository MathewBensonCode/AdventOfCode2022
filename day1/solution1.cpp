#include "input1.hpp"
#include "utility.hpp"
#include <print>

int main()
{
  const std::string_view inputstring{ inputdata };
  // const unsigned tiles = 8;

  std::vector<char> output(std::size(inputstring));


  utility::split_parallel_multi_pass(
    inputstring,
    output,
    [](const char first, char) -> bool {
      return !(first == '\n');
    });

  std::print("Collection {}", output);
}
