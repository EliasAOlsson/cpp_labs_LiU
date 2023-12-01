#include "functions.hpp"


int main(int argc, char* argv[]) {
  
  std::string file_name {};
  std::vector<std::string> arguments{};
  std::vector<std::string> text{};

  {
    std::vector<std::string> all_args {argv, argv + argc};
    
    if(all_args.size() < 2) {
      std::cout << "Error: a file must be specified." << std::endl;
      return 1;
    }
    file_name = all_args[1];

    auto iter {all_args.begin()};

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

  std::for_each(std::begin(arguments), std::end(arguments), [&text](std::string arg) -> void {
    std::pair<std::string, std::string> par;

    process_arg(arg, &par);

    if("" == par.first) {
      return;
    }

    if(par.first == "print"){
      print_flag(text);

    } else if (par.first == "frequency") {
      frequency_flag(text);

    } else if (par.first == "table") {
      table_flag(text); 

    } else if (par.first == "substitute") {
      substitute_flag(par.second, text);

    } else if (par.first == "remove") {
      remove_flag(par.second, text);

    } else {
      std::cout << "Error: flag not recognised." << std::endl;

    }

  }); //Lambda end

  return 0;
}










