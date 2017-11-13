#ifndef SUDOKU_FUNCT_H
#define SUDOKU_FUNCT_H

#include <iostream>
#include <string>
#include <vector>

bool finished_puzzle(const std::vector<std::string>& );
std::vector<int> find_indices (const int& , const int& );
int solve_or_guess(std::vector<std::string>&);
int find_col_box(const int& , const int& );
int find_row_box(const int&, const int& );
int find_max_given(const std::vector<std::string>&, const int&, const std::vector<int>& );
std::vector<int> find_zero_pos (std::string& );
void break_puzzle (std::vector<std::string>& );
int count_given(const std::string&);
int find_max_given (std::vector<std::string>& );
std::string convertInt(int);

#endif
