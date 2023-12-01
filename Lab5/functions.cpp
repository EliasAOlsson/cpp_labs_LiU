#include  "functions.hpp"

void print_flag(std::vector<std::string> const & text) {
  std::copy(std::begin(text), std::end(text), 
            std::ostream_iterator<std::string>{std::cout, " "});

  std::cout << std::endl;
}


void create_table(std::map<std::string, uint64_t>* table, std::vector<std::string> const & text) {

  std::for_each(std::begin(text), std::end(text), [&table](std::string word) -> void{

    ++((*table)[word]);
  });
}


void table_flag(std::vector<std::string> const & text) {
  std::map<std::string, uint64_t> table{};

  create_table(&table, text);

  std::for_each(std::begin(table), std::end(table), [](std::pair<std::string, uint64_t> par) {

    std::cout << std::left << std::setw(11) << par.first << " " << par.second << std::endl;
  });
}


void frequency_flag (std::vector<std::string> const & text) {
  std::map<std::string, uint64_t> table{};
  std::vector<std::pair<std::string, uint64_t>> frequency_table;

  create_table(&table, text);

  std::copy(std::begin(table), std::end(table), std::back_inserter(frequency_table));

  std::sort(std::begin(frequency_table), std::end(frequency_table), [](std::pair<std::string, uint64_t> lhs,
  std::pair<std::string, uint64_t> rhs) ->bool {

    return lhs.second > rhs.second;
  });
 
  std::for_each(std::begin(frequency_table), std::end(frequency_table), [](std::pair<std::string, uint64_t> par) {

    std::cout << std::right << std::setw(11) << par.first << " " << par.second << std::endl;
  }); 
}


void substitute_flag (std::string const & parameter, std::vector<std::string> & text)  {
  
  std::size_t found {parameter.find("+")};

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

  std::replace(std::begin(text), std::end(text), old_str, new_str);
}


void remove_flag (std::string const & parameter, std::vector<std::string> & text) {

  if("" == parameter) {

    std::cout << "Error: missing parameter for remove flag" << std::endl;
    return;
  }

  auto remove_end {std::remove(std::begin(text), std::end(text), parameter)};

  text.erase(remove_end, std::end(text));
}


void process_arg(std::string & argument, std::pair<std::string, std::string>* return_pair) {
  std::string flag{""};
  std::string parameter{""};

  if(argument.size() < 3) {
    std::cout << "Error: argument size too short. Bad format." << std::endl;
    return;
  }

  argument = argument.erase(0, 2);

  std::size_t found {argument.find("=")};

  if (found != std::string::npos) {
    parameter = argument.substr(found+1, argument.size());
  }

  flag = argument.substr(0, found);
  
  return_pair -> first = flag;
  return_pair -> second = parameter;
}



