#include "functions.h"
#include <fstream>

// Comment: Why are you using code blocks?
// If you want to separate the blocks content then use a function
//
// "Solution": The code blocks were removed

// TODO: Complementary work needed: Your program needs to handle unknown or 
// malformed flags or parameters. It should be clear to the user when they have 
// done something incorrect. 
//  
// Ex:  
// “--thisflagdoesnotexist” is not a valid argument  
// “--print=100” is not a valid argument 
// “--remove” is not a valid argument 
//
// Solution: Flags that should NOT have parameters now do show an error when a parameter is given. 

// TODO: Complementary work needed: Prefer to return the result instead of modifying a reference:
// For example:
// std::pair<std::string, std::string> par{process_arg(arg)};
// Note: This applies to other functions as well
//
// Solution: Solved in the following functions:
//  - process_arg
//  - create_table 

// TODO: Complementary work needed: Rename your files to use .h and .cc to follow the course standard
//
// Solution: The file types were changed.

int main(int argc, char* argv[]) {
  
  std::string file_name {};
  std::vector<std::string> arguments{};
  std::vector<std::string> text{};

 
  std::vector<std::string> all_args {argv, argv + argc};
  
  if(all_args.size() < 2) {
    std::cout << "Error: a file must be specified." << std::endl;
    return 1;
  }
  file_name = all_args[1];

  auto iter {all_args.begin()};

  iter = std::next(iter, 2);
  
  std::copy(iter, all_args.end(), std::back_inserter(arguments));
  
  
  std::ifstream file(file_name);

  if(!file.is_open()) {
    std::cout << "Error: the file couldn't be opened." << std::endl;
    return 1;
  }

  if(arguments.size() == 0) {
    std::cout << "Error: no arguments were given" << std::endl;
    return 1;
  }
  
  
  std::copy(std::istream_iterator<std::string>{file},
            std::istream_iterator<std::string>{}, 
            std::back_inserter(text));

  file.close();

  std::for_each(std::begin(arguments), std::end(arguments), [&text](std::string arg) -> void {
    std::pair<std::string, std::string> par {process_arg(arg)};

    if("" == par.first) {
      return;
    }

    if(par.first == "print"){
      if("" == par.second) {
        print_flag(text);

      } else {
        std::cout << "Error: the print flag doesn't accept parameters." << std::endl;
      }

    } else if (par.first == "frequency") {

      if("" == par.second) {
        frequency_flag(text);

      } else {
        std::cout << "Error: the frequency flag doesn't accept parameters." << std::endl;
      }
      
    } else if (par.first == "table") {
      if("" == par.second) {
        table_flag(text);

      } else {
        std::cout << "Error: the table flag doesn't accept parameters." << std::endl;
      }

    } else if (par.first == "substitute") {
      substitute_flag(par.second, text);

    } else if (par.first == "remove") {
      remove_flag(par.second, text);

    } else {
      std::cout << "Error: flag not recognised. Invalid argument." << std::endl;

    }

  }); //Lambda end

  return 0;
}










