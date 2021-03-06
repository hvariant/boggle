#pragma once

#include <utility>

enum Direction {
    U = 0, D, L, R,
    UR, UL, DR, DL, Direction_END
};

/*
 *  ----------> y
 *  | 0 1 2 3
 *  | 4 5 6 7
 *  | ...
 *  V
 *  x
 *
 *  --------------------------> y
 *  | (0,0) (0,1) (0,2) (0,3) 
 *  | (1,0) (1,1) (1,2) (1,3) 
 *  | ...
 *  V
 *  x
*/

bool check_bound(const std::pair<int,int>& xy, const int dim);
std::pair<int,int> go_dir(const int x, const int y, const Direction dir);
