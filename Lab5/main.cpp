#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {

  std::vector<std::string> arguments{};
  std::string file_name {};

  {
    std::vector<std::string> all_args {argv, argv + argc};

    file_name = all_args[1];

    auto iter = all_args.begin();

    iter = std::next(iter, 2);
    
    std::copy(iter, all_args.end(), std::back_inserter(arguments));
  }

  for(auto e : arguments) {

    std::cout << e << std::endl;
  }

  std::cout << "Filename: " << file_name << std::endl;

  std::ifstream file("test.txt");

  return 0;
}
