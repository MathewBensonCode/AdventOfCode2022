#include <iostream>
#include <sstream>
#include "input4.hpp"

int main() {
  std::stringstream inputstringstream{inputdata};

  if (!inputstringstream) {
    std::cerr << "Input File Not Found\n";
    return 1;
  }

  std::size_t count{};
  std::pair<std::size_t, std::size_t> pair1;
  std::pair<std::size_t, std::size_t> pair2;

  auto getpair = [](std::pair<std::size_t, std::size_t> &pair,
                    std::istream &input) {
    char delimiter{};
    input >> pair.first;
    input.get(delimiter);
    if (delimiter == '-') {
      input >> pair.second;
    }
  };

  auto getlinedata = [&](const std::string &linestring) {
    char delimiter{}; 
    std::stringstream linestream{linestring};
    getpair(pair1, linestream);
    linestream.get(delimiter);
    if (delimiter == ',') {
      getpair(pair2, linestream);
    }
  };

  while (!inputstringstream.eof()) {
    std::string linestring{};
    std::getline(inputstringstream, linestring);

    if (linestring.length() == 0) {
      continue;
    }

    getlinedata(linestring);

    std::cout<<"\nInput : " <<linestring<<'\n';

    std::cout<<"Pair 1 : "<<pair1.first<<"-"<<pair1.second<<'\n';
    std::cout<<"Pair 2 : "<<pair2.first<<"-"<<pair2.second<<'\n';

    if (((pair1.first <= pair2.first) && (pair1.second >= pair2.second)) ||  //pair2 fits in pair1
        ((pair1.first >= pair2.first) && (pair1.second <= pair2.second))) {  //pair1 fits in pair2
      std::cout<< " Found Match \n";
      count++;
    }
  }

  std::cout << "Total Found : " << count << '\n';
}
