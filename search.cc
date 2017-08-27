#include "search.h"
#include "common.h"
#include "ctpl_stl.h"
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

static void init_visited(vector<vector<bool> >& visited, const int dim){
    for(int i=0;i<dim;i++)
        visited.push_back(vector<bool>(dim,false));
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
        if(visited[new_xy.first][new_xy.second]){ // already visited
            continue;
        }

        path_count += _search_boggle_path_count(new_xy.first, new_xy.second, depth, visited, dim, min_len, max_len);
    }

    visited[x][y] = false;

    return path_count;
}

static int multiplier(const int x, const int y, const int dim){
    if(dim == 1) return 1;
    if(dim == 2) return 4;
    if(x >= (dim+1)/2 || y >= (dim+1)/2) return 0; // symmetric

    if(dim % 2 == 1 && x == dim/2 && x == y) return 1; // center position
    return 4;
}

uint_fast64_t search_boggle_path_count(const int dim, const int min_len, const int max_len, const int n_threads){
    vector<vector<uint_fast64_t> > counts; // dim x dim
    for(int i=0;i<dim;i++)
        counts.push_back(vector<uint_fast64_t>(dim,0));

    ctpl::thread_pool pool(n_threads);
    for(int x=0;x<(dim+1)/2;x++){
        for(int y=0;y<(dim+1)/2;y++){ // TODO: take symmetry into account
            pool.push([&counts, x, y, dim, min_len, max_len](int){
                vector<vector<bool> > visited;
                init_visited(visited, dim);
                counts[x][y] = _search_boggle_path_count(x, y, 0, visited, dim, min_len, max_len);
            });
        }
    }
    pool.stop(true); // join all threads

    for(size_t x=0;x<counts.size();x++){
        for(size_t y=0;y<counts[x].size();y++){
            cerr << "(" << x << "," << y << "): " << counts[x][y] << "x" << multiplier(x,y,dim) << endl;
            counts[x][y] = counts[x][y] * multiplier(x,y,dim);
        }
    }

    uint_fast64_t path_count = std::accumulate(
        counts.begin(), counts.end(), 0ULL, /* need to write 0ULL instead of 0 to avoid overflow */
        [] (const uint_fast64_t acc, const vector<uint_fast64_t>& row) {
            return acc + std::accumulate(row.begin(), row.end(), 0ULL);
        }
    );

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
        if(visited[new_xy.first][new_xy.second]){ // already visited
            continue;
        }

        _search_boggle(new_xy.first, new_xy.second, word, visited, words, board, dict, dim);
    }

    visited[x][y] = false;
    word.pop_back();
}

set<string> search_boggle(const vector<vector<char> >& board, const boggle_dict& dict, const int n_threads){
    const int dim = board.size();

    set<string> words;
    for(int x=0;x<dim;x++){
        for(int y=0;y<dim;y++){
            vector<vector<bool> > visited;
            init_visited(visited, dim);

            string word;
            vector<string> _words;
            _search_boggle(x, y, word, visited, _words, board, dict, dim);

            std::for_each(_words.begin(), _words.end(),
                [&words](const string& word){
                    words.insert(word);
                }
            );
        }
    }

    return words;
}
