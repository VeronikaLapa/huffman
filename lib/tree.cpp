#include "tree.h"
#include <vector>
#include <algorithm>
#include "file_exceptions.h"


using namespace std;

bool node_comp(pair<node, unsigned long long> a, pair<node, unsigned long long> b) {
    return a.second < b.second;
}

huff_tree::huff_tree() : root(nullptr) {}

huff_tree::huff_tree(char_counter &count) {
    vector<pair<node *, unsigned long long>> build_list;
    for (unsigned int i = 0; i < MAX_CHAR; i++) {
        if (count.char_amt(i) > 0) {
            build_list.push_back(pair<node *, unsigned long long>(new node(i), count.char_amt(i)));
        }
    }
    while (build_list.size() > 1) {
        sort(build_list.begin(), build_list.end(),
             [](const pair<node *, unsigned long long> &a, const pair<node *, unsigned long long> &b) -> bool {
                 return a.second > b.second;
             });
        pair<node *, unsigned long long> join_el;
        join_el.second = build_list[build_list.size() - 1].second + build_list[build_list.size() - 2].second;
        join_el.first = new node(build_list[build_list.size() - 1].first, build_list[build_list.size() - 2].first);
        build_list.pop_back();
        build_list.pop_back();
        build_list.push_back(join_el);
    }
    if (build_list.size() == 1) {
        root = build_list[0].first;
        build_dict();

    } else {
        root = nullptr;
    }
}

huff_tree::huff_tree(const huff_tree &obj) {
    root = new node();
    dict = obj.dict;
    copy_nodes(root, obj.root);
}

void copy_nodes(node *to, node *from) {
    to->symbol = from->symbol;
    if (from->left != nullptr) {
        to->left = new node();
        copy_nodes(to->left, from->left);
    }
    if (from->right != nullptr) {
        to->right = new node();
        copy_nodes(to->right, from->right);
    }
}

huff_tree::huff_tree(bit_string& str, size_t &ind) {
    if (!str.get_bit(ind)) {
        root = nullptr;
        ++ind;
        return;
    } else {
        root = new node();
        vector<node *> list;
        build_tree(root, str, ++ind, list);
        for (size_t i = 0; i < list.size(); i++) {
            char symb = 0;
            for (size_t pos = 0; pos < CHAR_SIZE; pos++) {
                symb = (symb << 1) + str.get_bit(ind++);
            }
            list[i]->symbol = symb;

        }
    }
    build_dict();
}

/*
void huff_tree::build_tree(node *crt_node, bit_string str, size_t &ind, vector<node *> &list) {
    if (str.get_bit(ind) && crt_node->left == nullptr) {
        crt_node->left = new node();
        build_tree(crt_node->left, str, ++ind, list);
        if (str.get_bit(ind) && crt_node->right == nullptr) {
            crt_node->right = new node();
            build_tree(crt_node->right, str, ++ind, list);
        }
    }
    if (!str.get_bit(ind) && crt_node->is_leaf()) {
        list.push_back(crt_node);
        ++ind;
    } else if (str.get_bit(ind)) {
        throw corrupt_file();
    } else {
        ++ind;
    }
}
*/
void huff_tree::build_tree(node *crt_node, bit_string str, size_t &ind, vector<node *> &list) {
    if (str.get_bit(ind) && crt_node->left == nullptr) {
        crt_node->left = new node();
        build_tree(crt_node->left, str, ++ind, list);
        crt_node->right = new node();
        build_tree(crt_node->right, str, ind, list);
    }
    if (!str.get_bit(ind) && crt_node->is_leaf()) {
        list.push_back(crt_node);
        ++ind;
    }
}
void delete_nodes(node *root) {
    if (root != nullptr) {
        if (root->left != nullptr) {
            delete_nodes(root->left);
        }
        if (root->right != nullptr) {
            delete_nodes(root->right);
        }
        delete root;
    }
}

huff_tree::~huff_tree() {
    delete_nodes(root);
}

huff_tree &huff_tree::operator=(huff_tree other) {
    swap(this->root, other.root);
    swap(this->dict, other.dict);
    return *this;
}

void huff_tree::dfs(node *n, bit_code crt_code) {
    if (n->left != nullptr) {
        crt_code.add_bit(0);
        dfs(n->left, crt_code);
        crt_code.erase_bit();
    }
    if (n->right != nullptr) {
        crt_code.add_bit(1);
        dfs(n->right, crt_code);
        crt_code.erase_bit();
    }
    if (n->is_leaf()) {
        crt_code.reverse();
        dict.insert({n->symbol, crt_code});
    }
}

void huff_tree::build_dict() {
    if (root->is_leaf()) {
        bit_code c = bit_code();
        c.add_bit(1);
        dict.insert({root->symbol, c});
    } else {
        dfs(root, bit_code());
    }
}

bit_code huff_tree::get_code(char ch) {
    return (dict.find(ch)->second);
}
/*
void huff_tree::tree_struct_to_string(node *crt_node, bit_string &order, bit_string &tree) {
    if (crt_node == nullptr) {
        tree.add_bit(0);
        return;
    } else if (crt_node == root) {
        tree.add_bit(1);
    }
    if (crt_node->is_leaf()) {
        order.add_code(crt_node->symbol);
        tree.add_bit(0);
        return;
    }
    if (crt_node->left != nullptr) {
        tree.add_bit(1);
        tree_struct_to_string(crt_node->left, order, tree);
    }
    if (crt_node->right != nullptr) {
        tree.add_bit(1);
        tree_struct_to_string(crt_node->right, order, tree);
    }
    tree.add_bit(0);
}
*/
void huff_tree::tree_struct_to_string(node *crt_node, bit_string &order, bit_string &tree) {
    if (crt_node == nullptr) {
        tree.add_bit(0);
        return;
    } else if (crt_node == root) {
        tree.add_bit(1);
    }
    if (crt_node->is_leaf()) {
        order.add_code(crt_node->symbol);
        tree.add_bit(0);
        return;
    }
    if (crt_node->left != nullptr) {
        tree.add_bit(1);
        tree_struct_to_string(crt_node->left, order, tree);
    }
    if (crt_node->right != nullptr) {
        //tree.add_bit(1);
        tree_struct_to_string(crt_node->right, order, tree);
    }
    //tree.add_bit(0);
}
char huff_tree::get_char(bit_string str, size_t &ind) {

    node *crt_node = root;
    while (!crt_node->is_leaf() && ind <= str.size()) {
        if (!str.get_bit(ind)) {
            crt_node = crt_node->left;
        } else {
            crt_node = crt_node->right;
        }
        ++ind;
    }
    if(crt_node == root) {
        ++ind;
    }
    return crt_node->symbol;
}

bit_string huff_tree::to_string() {
    bit_string order;
    bit_string tree;
    tree_struct_to_string(root, order, tree);
    tree.concat(order);
    return tree;
}