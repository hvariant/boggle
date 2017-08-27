#pragma once

#include <vector>
#include <cstdint>
#include <set>
#include "boggle_dict.h"

uint_fast64_t search_boggle_path_count(const int dim, const int min_len, const int max_len);
std::set<std::string> search_boggle(const std::vector<std::vector<char> >& board, const boggle_dict& dict);
