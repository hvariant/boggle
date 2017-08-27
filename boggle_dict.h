#pragma once

#include <string>
#include <map>

class boggle_dict {
public:
    // build boggle_dict from file
    boggle_dict(const std::string& file);

    bool has_prefix(const std::string& word) const;
    bool has_word(const std::string& word) const;

private:
    typedef struct _boggle_dict_node {
        bool is_word = false;
        std::map<char, struct _boggle_dict_node> children;
    } boggle_dict_node;

    boggle_dict_node root;

    void insert_word(const std::string& word);
    const boggle_dict_node* find_node(const std::string& word) const;
    boggle_dict_node* find_node_insert(const std::string& word);
};
