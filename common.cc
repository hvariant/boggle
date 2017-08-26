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

pair<int,int> ind_to_xy(const int i, const int dim){
    int y = i % dim;
    int x = i / dim;

    //assert(x >= 0 && x < dim);
    //assert(y >= 0 && y < dim);

    return pair<int,int>(x,y);
}

int xy_to_ind(const pair<int,int>& xy, const int dim){
    int i = xy.first * dim + xy.second;

    //assert(i >= 0 && i < dim*dim);

    return i;
}

int xy_to_ind(const int x, const int y, const int dim){
    return x * dim + y;
}

bool check_bound(const pair<int,int>& xy, const int dim){
    return xy.first >= 0 && xy.first < dim && xy.second >=0 && xy.second < dim;
}

pair<int,int> go_dir(const int x, const int y, const Direction dir){
    pair<int,int> xy = {x,y};

    // speed up using table?
    if(dir == U || dir == UL || dir == UR){ // upward
        xy.first--;
    }
    if(dir == D || dir == DL || dir == DR){ // downward
        xy.first++;
    }
    if(dir == L || dir == DL || dir == UL){ // to left
        xy.second--;
    }
    if(dir == R || dir == DR || dir == UR){ // to right
        xy.second++;
    }

    return xy;
}
