#include <algorithm>
#include <complex>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

//#include "functions.hpp"

std::vector<std::string> text{};

void print_flag() {

 auto print = [](const std::string& n) { std::cout << n << ' '; };
 
    std::cout << std::endl;
    std::for_each(text.cbegin(), text.cend(), print);
    std::cout << '\n'; 
}

void table_flag() {


}

void frequency_flag () {



}

void substitute_flag (std::string const & parameter)  {


}

void remove_flag (std::string const & parameter) {


}


void process_arg(std::string argument) 
{
  std::string flag{};
  std::string parameter{""};
  //std::string argument{};

  if(argument.size() < 2) {
    std::cout << "Error: argument size too short. Bad format." << std::endl;
    return;
  }

  argument = argument.erase(0, 2);

  std::size_t found = argument.find("=");

  if (found != std::string::npos) {

    parameter = argument.substr(found+1, argument.length());
  }

  flag = argument.substr(0, found);
  
  if(flag == "print"){
    print_flag();

  } else if (flag == "frequency") {


  } else if (flag == "table") {


  } else if (flag == "substitute") {


  } else if (flag == "remove") {


  } else {

    std::cout << "Error: flag not recognised." << std::endl;
  }

  //std::cout << "Flag: " << flag << std::endl << "Parameter: " << parameter << std::endl; 
  
}


int main(int argc, char* argv[]) {
  
  std::string file_name {};
  std::vector<std::string> arguments{};

  {
    std::vector<std::string> all_args {argv, argv + argc};
    
    if(all_args.size() < 2) {

      std::cout << "Error: a file must be specified." << std::endl;
      return 1;
    }
    file_name = all_args[1];

    auto iter = all_args.begin();

    iter = std::next(iter, 2);
    
    std::copy(iter, all_args.end(), std::back_inserter(arguments));
  }
  
  std::ifstream file(file_name);

  if(!file.is_open()) {

    std::cout << "Error: the file couldn't be opened." << std::endl;
    return 1;
  }

  if(arguments.size() == 0) {

    std::cout << "Error: no arguments were given" << std::endl;
    return 1;
  }
  
  //======================= The method must be changed (full STL approach)
  { 
    std::string word;

    while(file >> word) {
      text.push_back(word);
    }
  }

  file.close();

  std::for_each(arguments.begin(), arguments.end(), process_arg);

  return 0;
}










