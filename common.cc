#include "common.h"
#include <cassert>

using namespace std;

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

bool check_bound(const pair<int,int>& xy, const int dim){
    return xy.first >= 0 && xy.first < dim && xy.second >=0 && xy.second < dim;
}

/*
    U = 0, D, L, R,
    UR, UL, DR, DL, Direction_END
*/
static int delta_x[] = {
    -1, 1, 0, 0,
    -1, -1, 1, 1,
};
static int delta_y[] = {
    0, 0, -1, 1,
    1, -1, 1, -1,
};

pair<int,int> go_dir(const int x, const int y, const Direction dir){
    pair<int,int> xy = {x,y};

    xy.first += delta_x[(int)dir];
    xy.second += delta_y[(int)dir];

    return xy;
}
