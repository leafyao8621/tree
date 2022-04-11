#include "core.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <list>

Core::Tree::Tree(std::string fn) {
    std::ifstream ifs(fn);
    if (ifs.fail()) {
        throw Core::Tree::Err::FILE_ACCESS;
    }
    uint64_t n_nodes = 0;
    ifs >> n_nodes;
    this->nodes.resize(n_nodes);
    for (auto &i : this->nodes) {
        i = new Node();
        i->down_calculated = false;
        i->up_calculated = false;
    }
    double min = 0;
    this->root = nullptr;
    for (auto &i : this->nodes) {
        double value = 0;
        int64_t left = 0;
        int64_t right = 0;
        ifs >> value >> left >> right;
        if (!min || value < min) {
            min = value;
        }
        i->value = value;
        i->left = left >= 0 ? this->nodes[left] : nullptr;
        i->right = right >= 0 ? this->nodes[right] : nullptr;
    }
    this->nodes[0]->down_calculated = true;
    this->nodes[0]->down_sum = this->nodes[0]->value;
    this->root = this->nodes[0];
    this->up_calculated = false;
    this->n_inf = min < 0 ? min * n_nodes : -1;
}

Core::Tree::~Tree() {
    for (auto &i : this->nodes) {
        delete i;
    }
}

double Core::Tree::max_sum_down() {
    if (!this->root) {
        throw Core::Tree::Err::EMPTY_TREE;
    }
    double out = this->root->down_sum;
    std::list<Node*> stack;
    stack.push_back(this->root);
    for (; stack.size();) {
        Node *cur = stack.back();
        stack.pop_back();
        if (cur->down_sum > out) {
            out = cur->down_sum;
        }
        if (cur->left) {
            if (!cur->left->down_calculated) {
                cur->left->down_sum = cur->down_sum + cur->left->value;
            }
            stack.push_back(cur->left);
        }
        if (cur->right) {
            if (!cur->right->down_calculated) {
                cur->right->down_sum = cur->down_sum + cur->right->value;
            }
            stack.push_back(cur->right);
        }
    }
    return out;
}

double Core::Tree::max_sum_up() {
    if (!this->root) {
        throw Core::Tree::Err::EMPTY_TREE;
    }
    for (auto &i : this->nodes) {
        i->visited = false;
    }
    double out = this->n_inf;
    std::list<Node*> stack;
    stack.push_back(this->root);
    for (; stack.size();) {
        Node *cur = stack.back();
        if (this->up_calculated) {
            stack.pop_back();
        }
        bool left = false;
        bool right = false;
        if (cur->left && !cur->left->visited) {
            cur->left->visited = true;
            stack.push_back(cur->left);
        } else {
            left = true;
            if (!cur->up_calculated && cur->left) {
                cur->up_sum += cur->left->up_sum;
            }
        }
        if (cur->right && !cur->right->visited) {
            cur->right->visited = true;
            stack.push_back(cur->right);
        } else {
            right = true;
            if (!cur->up_calculated && cur->right) {
                cur->up_sum += cur->right->up_sum;
            }
        }
        if (!cur->up_calculated && left && right) {
            stack.pop_back();
            cur->up_calculated = true;
            cur->up_sum += cur->value;
        }
        if (cur->up_calculated && cur->up_sum > out) {
            out = cur->up_sum;
        }
    }
    this->up_calculated = true;
    return out;
}
