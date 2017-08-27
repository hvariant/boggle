#include "boggle_gen.h"
#include <random>
#include <ctype.h>
#include <iostream>
#include <assert.h>

using namespace std;

static vector<vector<char> > _boggle_gen(mt19937& rng, const char** dice, const int dim){
    uniform_int_distribution<int> uni(0,5); // closed range

    vector<vector<char> > ret;
    for(int i=0;i<4;i++){
        ret.push_back(vector<char>());
        for(int j=0;j<4;j++){
            auto outcome = uni(rng);
            char c = dice[i*4+j][outcome];
            
            ret[i].push_back(tolower(c));
        }
    }
    
    return ret;
}

vector<vector<char> > boggle_gen4(const bool classic, const int seed){
    random_device rd;
    mt19937 rng(rd());
    if(seed != -1) rng.seed(seed);

    const char** dice = new_boggle4;
    if(classic) dice = classic_boggle4;

    // mfw RVO: https://stackoverflow.com/questions/17473753/c11-return-value-optimization-or-move/17473869#17473869
    return _boggle_gen(rng, dice, 4);
}

vector<vector<char> > boggle_gen5(const int seed){
    random_device rd;
    mt19937 rng(rd());
    if(seed != -1) rng.seed(seed);

    return _boggle_gen(rng, boggle5, 5);
}

vector<vector<char> > boggle_genn(const int dim, const int seed){
    cerr << "generation of boggle with random dimension not implemented yet" << endl;
    assert(false);

    // never reach this
    return vector<vector<char> >();
}
