#pragma once

#include <vector>

extern const char* classic_boggle4[];
extern const char* new_boggle4[];
extern const char* boggle5[];

std::vector<std::vector<char> > boggle_gen4(const bool classic=false, const int seed=-1);
std::vector<std::vector<char> > boggle_gen5(const int seed=-1);
std::vector<std::vector<char> > boggle_genn(const int dim, const int seed=-1);
