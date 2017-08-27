#include "boggle_dict.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;

const string file = "dictionary.txt";

int main(void){
    auto start = chrono::high_resolution_clock::now();
    boggle_dict dict(file);
    auto end = chrono::high_resolution_clock::now();
    auto i_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    cerr << "took " << i_ms.count() << " ms to build dictionary" << endl;

    ifstream in(file);
    while(!in.eof()){
        string word;
        in >> word;

        if(!dict.has_word(word)){
            cout << "word " << word << " doesn't exist in the dictionary!" << endl;
        }
        
        for(size_t len=1;len<word.size();len++){
            string prefix = word.substr(0,len);
            if(!dict.has_prefix(prefix)){
                cout << "prefix " << prefix << " doesn't exit in the dictionary!" << endl;
            }
        }
    }
    in.close();

    return 0;
}
