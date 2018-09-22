#ifndef TREE_H
#define TREE_H

#include "char_counter.h"
#include <memory>
#include <map>
#include "code.h"
#include "bit_string.h"
#include <vector>
struct node {
    node(): left(nullptr), right(nullptr), symbol(0){};
    node(char ch) : left(nullptr), right(nullptr),  symbol(ch){};
    node(node* l, node* r) : left(l), right(r){};
    node* left;
    node* right;
    char symbol;
    bool is_leaf() {return left == nullptr && right == nullptr;};
};
class huff_tree {
public:
    huff_tree();
    huff_tree(char_counter& count);
    huff_tree(bit_string& , size_t& ind);
    huff_tree(const huff_tree& obj);
    huff_tree & operator = (huff_tree other);
    bit_code get_code(char ch);
    char get_char(bit_string& str, size_t& ind);
    ~huff_tree();
    bit_string to_string();
    bool is_empty() {return root==nullptr;}
private:
    void build_tree(node* crt_node, bit_string& str, size_t& ind, std::vector<node*>& list);
    void tree_struct_to_string(node* crt_node, bit_string& order, bit_string& tree);
    void dfs (node* n, bit_code crt_code);
    void build_dict();
    node* root;
    std::map<char, bit_code> dict;

};

void delete_nodes(node* n);
void copy_nodes(node* to, node* from);
#endif //TREE_H
