#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>


std::vector<std::string> text{};

void print_flag() {
  std::copy(text.begin(), text.end(), 
            std::ostream_iterator<std::string>{std::cout, " "});

  std::cout << std::endl;
}

void table_flag() {
  std::map<std::string, uint64_t> table{};

  std::for_each(text.begin(), text.end(), [&table](std::string word){

    ++table[word];
  });

  std::for_each(table.begin(), table.end(), [](std::pair<std::string, uint64_t> par) {

    std::cout << std::left << std::setw(11) << par.first << " " << par.second << std::endl;
  });
}

void frequency_flag () {


}

void substitute_flag (std::string const & parameter)  {
  
  std::size_t found = parameter.find("+");

  if(std::string::npos == found) {

    std::cout << "Error: parameter for substitute flag is invalid." << std::endl;
    return;
  }
  if(0 == found) {

    std::cout << "Error: missing first parameter for substitution flag." << std::endl;
    return;
  }
  if(parameter.size()-1 == found) {

    std::cout << "Error: missing second parameter for substitution flag. " << std::endl;
    return;
  }

  std::string old_str {parameter.substr(0, found)};

  std::string new_str {parameter.substr(found + 1, parameter.size())};

  std::replace(text.begin(), text.end(), old_str, new_str);
}

void remove_flag (std::string const & parameter) {

  if("" == parameter) {

    std::cout << "Error: missing parameter for remove flag" << std::endl;
    return;
  }

  auto remove_end {std::remove(text.begin(), text.end(), parameter)};

  text.erase(remove_end, text.end());
}


void process_arg(std::string argument) 
{
  std::string flag{};
  std::string parameter{""};

  if(argument.size() < 3) {
    std::cout << "Error: argument size too short. Bad format." << std::endl;
    return;
  }

  argument = argument.erase(0, 2);

  std::size_t found = argument.find("=");

  if (found != std::string::npos) {
    parameter = argument.substr(found+1, argument.size());
  }

  flag = argument.substr(0, found);
  
  if(flag == "print"){
    print_flag();

  } else if (flag == "frequency") {
    frequency_flag();

  } else if (flag == "table") {
    table_flag(); 

  } else if (flag == "substitute") {
    substitute_flag(parameter);

  } else if (flag == "remove") {
    remove_flag(parameter);

  } else {
    std::cout << "Error: flag not recognised." << std::endl;

  }
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
  
  { 
    std::copy(std::istream_iterator<std::string>{file},
              std::istream_iterator<std::string>{}, 
              std::back_inserter(text));
  }

  file.close();

  std::for_each(arguments.begin(), arguments.end(), process_arg);

  return 0;
}










