#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>


void print_flag(std::vector<std::string> const &);
void create_table(std::map<std::string, uint64_t>*, std::vector<std::string> const &);
void table_flag(std::vector<std::string> const &);
void frequency_flag (std::vector<std::string> const &);
void substitute_flag (std::string const &, std::vector<std::string> &);
void remove_flag (std::string const &, std::vector<std::string> &);
void process_arg(std::string &, std::pair<std::string, std::string>*); 


#endif
