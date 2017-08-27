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

static uint_fast64_t _search_boggle_path_count(int x, int y, int depth, vector<vector<bool> >& visited, const int dim, const int min_len, const int max_len){
    visited[x][y] = true;
    depth++;

    uint_fast64_t path_count = 0;

    if(depth > max_len){ // no need to keep searching
        visited[x][y] = false;

        return path_count;
    }
    if(depth >= min_len){
        path_count++;
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

        path_count += _search_boggle_path_count(new_xy.first, new_xy.second, depth, visited, dim, min_len, max_len);
    }

    visited[x][y] = false;

    return path_count;
}

uint_fast64_t search_boggle_path_count(const int dim, const int min_len, const int max_len){
    if(DEBUG){
        cerr << endl << endl;
        cerr << "+search_boggle_paths" << endl;
        cerr << "dim:" << dim << endl;
        cerr << "min_len:" << min_len << endl;
        cerr << "max_len:" << max_len << endl;
    }

    uint_fast64_t path_count = 0;

    // TODO: parallelise this
    for(int x=0;x<dim;x++){
        for(int y=0;y<dim;y++){ // TODO: take symmetry into account
            vector<vector<bool> > visited;
            init_visited(visited, dim);
            path_count += _search_boggle_path_count(x, y, 0, visited, dim, min_len, max_len);
        }
    }

    if(DEBUG){
        cerr << "-search_boggle_paths" << endl;
    }

    return path_count;
}

static void _search_boggle(int x, int y, string& word, vector<vector<bool> >& visited, vector<string>& words,
        const vector<vector<char> >& board, const boggle_dict& dict, const int dim){
    visited[x][y] = true;
    word.push_back(board[x][y]);

    int depth = word.size();
    if(depth > dim*dim || !dict.has_prefix(word)){ // no need to keep searching
        visited[x][y] = false;
        word.pop_back();

        return;
    }

    if(dict.has_word(word))
        words.push_back(word);

    for(int i=0;i<Direction_END;i++){
        Direction dir = (Direction)i;
        pair<int,int> new_xy = go_dir(x, y, dir);

        if(!check_bound(new_xy, dim)){ // out of bound
            continue;
        }
        if(check_visited(new_xy, visited)){ // already visited
            continue;
        }

        _search_boggle(new_xy.first, new_xy.second, word, visited, words, board, dict, dim);
    }

    visited[x][y] = false;
    word.pop_back();
}

set<string> search_boggle(const vector<vector<char> >& board, const boggle_dict& dict){
    const int dim = board.size();

    set<string> words;
    for(int x=0;x<dim;x++){
        for(int y=0;y<dim;y++){
            vector<vector<bool> > visited;
            init_visited(visited, dim);

            string word;
            vector<string> _words;
            _search_boggle(x, y, word, visited, _words, board, dict, dim);

            for(const auto& it : _words)
                words.insert(it);
        }
    }

    return words;
}
