#include "boggle_dict.h"
#include <fstream>
#include <iostream>

using namespace std;

boggle_dict::boggle_dict(const string& file){
    ifstream in(file);

    if(!in.is_open()){
        cerr << "cannot open " << file << endl;
        return;
    }

    while(!in.eof()){
        string word;
        in >> word;

        insert_word(word);
    }
}

const boggle_dict::boggle_dict_node* boggle_dict::find_node(const std::string& word) const{
    const boggle_dict_node* cur = &root;

    for(size_t i=0;i<word.size();i++){
        char c = word[i];
        if(cur->children.find(c) == cur->children.end()){ // no prefix
            return NULL;
        }

        auto it = cur->children.find(c);
        cur = &(it->second);
    }

    return cur;
}

boggle_dict::boggle_dict_node* boggle_dict::find_node_insert(const std::string& word){
    boggle_dict_node* cur = &root;

    for(size_t i=0;i<word.size();i++){
        char c = word[i];
        if(cur->children.find(c) == cur->children.end()){ // no prefix
            cur->children.insert(
                pair<char, boggle_dict_node>(
                    c, boggle_dict_node()
                )
            );
        }

        auto it = cur->children.find(c);
        cur = &(it->second);
    }

    return cur;
}

bool boggle_dict::has_prefix(const string& word) const{
    return find_node(word) != NULL;
}

bool boggle_dict::has_word(const string& word) const{
    const boggle_dict_node* n = find_node(word);
    return n != NULL && n->is_word;
}

void boggle_dict::insert_word(const string& word){
    boggle_dict_node* n = find_node_insert(word);
    n->is_word = true;
}
