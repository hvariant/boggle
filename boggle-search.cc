#include <iostream>
#include <string>
#include <vector>
#include "search.h"
#include "common.h"

using namespace std;

int main(int argc, char* argv[]){
    // default arguments
    int dim = 4;
    int min_len = 1;
    int max_len = dim*dim;

    for (int i = 1; i < argc; i+=2) {
        string arg = argv[i];
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
        } else {
            cerr << "Unknown argument " << arg << endl;
            return 1;
        }
    }

    cerr << "dim=" << dim << endl;
    cerr << "min_len=" << min_len << endl;
    cerr << "max_len=" << max_len << endl;

    vector<vector<int> > paths;
    search_boggle_paths(dim, min_len, max_len, paths);

    cout << "number of paths: " << paths.size() << endl;

    return 0;
}
