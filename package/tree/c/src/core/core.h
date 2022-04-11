#ifndef _CORE_H_
#define _CORE_H_

#include <stdint.h>
#include <stdbool.h>

#define ERR_NULL_PTR 1
#define ERR_FILE_ACCESS 2
#define ERR_EMPTY_TREE 3

struct Tree {
    struct TreeNode *root;
    uint64_t n_nodes;
    struct TreeNode **nodes;
    bool up_calculated;
    double n_inf;
};

int tree_initialize(struct Tree *tree, const char *fn);
int tree_max_sum_down(struct Tree *tree, double *out);
int tree_max_sum_up(struct Tree *tree, double *out);
int tree_finalize(struct Tree *tree);

#endif
