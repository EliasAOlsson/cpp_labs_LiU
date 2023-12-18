#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

// TODO: Complementary work needed: Move includes only used in the .cc file to the .cc file
//
// Solutions: 
//  - Moved <iomanip> to functions.cc
//  - Moved <fstream> to main.cc

// TODO: Complementary work needed: Use variable names for the arguments in the header. The names should clearly indicate what the arguments mean to a programmer that wants to use your functions
//
// Solution: the function's arguments have names now.

// TODO: Complementary work needed: Do not mix references and pointers
//
// Solution: The use of pointers and references (together) is now avoided.

void print_flag(std::vector<std::string> const & text);
std::map<std::string, uint64_t> create_table(std::vector<std::string> const & text);  // Now it returns the table.
void table_flag(std::vector<std::string> const & text);
void frequency_flag (std::vector<std::string> const & text);
void substitute_flag (std::string const & parameter, std::vector<std::string> & text);
void remove_flag (std::string const & parameter, std::vector<std::string> & text);
std::pair<std::string, std::string> process_arg(std::string & unprocessed_argument); 

#endif
