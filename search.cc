#include "search.h"
#include "common.h"
#include <iostream>

using namespace std;

static void init_visited(vector<vector<bool> >& visited, const int dim){
    for(int i=0;i<dim;i++)
        visited.push_back(vector<bool>(dim,false));
}

static bool check_visited(const pair<int, int>& xy, const vector<vector<bool> >& visited){
    return visited[xy.first][xy.second];
}

static void _search_boggle_paths(int x, int y, vector<vector<bool> >& visited, vector<int>& path, vector<vector<int> >& paths, const int dim, const int min_len, const int max_len){
    int idx = xy_to_ind(x,y,dim);

    visited[x][y] = true;
    path.push_back(idx);

    int depth = path.size();
    if(depth >= min_len){
        paths.push_back(path);

        if(DEBUG && paths.size() % 10000 == 0){
            cerr << paths.size() << endl;
        }
    }
    if(depth > max_len){ // no need to keep searching
        path.pop_back();
        visited[x][y] = false;

        return;
    }

    for(int i=0;i<Direction_END;i++){
        Direction dir = (Direction)i;
        pair<int,int> new_xy = go_dir(x, y, dir);

        if(!check_bound(new_xy, dim)){ // out of bound
            continue;
        }
        if(check_visited(new_xy, visited)){ // already visited
            continue;
        }

        _search_boggle_paths(new_xy.first, new_xy.second, visited, path, paths, dim, min_len, max_len);
    }

    path.pop_back();
    visited[x][y] = false;
}

void search_boggle_paths(const int dim, const int min_len, const int max_len, vector<vector<int> >& paths){
    if(DEBUG){
        cerr << endl << endl;
        cerr << "+search_boggle_paths" << endl;
        cerr << "dim:" << dim << endl;
        cerr << "min_len:" << min_len << endl;
        cerr << "max_len:" << max_len << endl;
    }

    // TODO: parallelise this
    for(int x=0;x<dim;x++){
        for(int y=0;y<dim;y++){ // TODO: take symmetry into account
            vector<vector<bool> > visited;
            init_visited(visited, dim);
            vector<int> path;
            _search_boggle_paths(x, y, visited, path, paths, dim, min_len, max_len);
        }
    }

    if(DEBUG){
        cerr << "-search_boggle_paths" << endl;
    }
}
