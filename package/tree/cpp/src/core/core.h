#ifndef _CORE_H_
#define _CORE_H_

#include <vector>
#include <string>

namespace Core {
    class Tree {
        struct Node {
            double value;
            Node *left, *right;
            double up_sum, down_sum;
            bool up_calculated, down_calculated, visited;
        };
        bool up_calculated;
        double n_inf;
        Node *root;
        std::vector<Node*> nodes;
    public:
        enum Err {
            FILE_ACCESS,
            EMPTY_TREE
        };
        Tree(std::string fn);
        ~Tree();
        double max_sum_up();
        double max_sum_down();
    };
}

#endif
