#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "search.h"
#include "common.h"
#include "boggle_gen.h"

using namespace std;

int main(int argc, char* argv[]){
    // default arguments
    int dim = 4;
    int min_len = 1;
    int max_len = -1;
    bool count = false;
    bool classic = false;
    string dict_fn = "dictionary.txt";
    int seed = -1;
    int n_threads = 1;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        // options that doesn't take argument
        if(arg == "-c"){
            count = true;
            continue;
        } else if(arg == "--classic"){
            classic = true;
            continue;
        }

        // options that take arguments
        if(i+1 >= argc){
            cerr << "Missing value for argument " << arg << endl;
            return 1;
        }
        string val = argv[i+1];

        if (arg == "-d") {
            dim = stoi(val);
        } else if (arg  == "-m") {
            min_len = stoi(val);
        } else if (arg  == "-M") {
            max_len = stoi(val);
        } else if (arg  == "-i") {
            dict_fn = val;
        } else if (arg  == "-r") {
            seed = stoi(val);
        } else if (arg  == "-p") {
            n_threads = stoi(val);
        } else {
            cerr << "Unknown argument " << arg << endl;
            return 1;
        }

        i++;
    }
    if(max_len == -1) max_len = dim*dim;

    cerr << "dim=" << dim << endl;
    cerr << "min_len=" << min_len << endl;
    cerr << "max_len=" << max_len << endl;
    cerr << "count=" << count << endl;
    cerr << "classic=" << classic << endl;
    cerr << "dict_fn=" << dict_fn << endl;
    cerr << "seed=" << seed << endl;
    cerr << "n_threads=" << n_threads << endl;
    cerr << endl << endl;

    if(count){
        uint_fast64_t path_count = search_boggle_path_count(dim, min_len, max_len, n_threads);
        cout << "number of paths: " << path_count << endl;
    } else {
        vector<vector<char> > board;
        if(dim == 4){
            board = boggle_gen4(seed, classic);
        } else if(dim == 5){
            board = boggle_gen5(seed);
        } else {
            board = boggle_genn(seed,dim);
        }

        cout << "Board:" << endl;
        for(size_t i=0;i<board.size();i++){
            for(size_t j=0;j<board[i].size();j++){
                cout << board[i][j];
            }
            cout << endl;
        }
        cout << endl;

        boggle_dict dict(dict_fn);
        set<string> words = search_boggle(board, dict, n_threads);

        cout << "List of words:" << endl;
        for(const auto& s : words)
            cout << s << endl;
    }

    return 0;
}
