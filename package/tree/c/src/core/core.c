#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    double value;
    bool up_calculated, down_calculated;
    double up_sum;
    double down_sum;
    struct TreeNode *left;
    struct TreeNode *right;
};

int tree_initialize(struct Tree *tree, const char *fn) {
    if (!tree || !fn) {
        return ERR_NULL_PTR;
    }
    FILE *fin = fopen(fn, "r");
    if (!fin) {
        return ERR_FILE_ACCESS;
    }
    fscanf(fin, "%lu", &tree->n_nodes);
    tree->nodes = malloc(sizeof(struct TreeNode*) * tree->n_nodes);
    struct TreeNode **iter = tree->nodes;
    for (uint64_t i = 0; i < tree->n_nodes; ++i, ++iter) {
        *iter = malloc(sizeof(struct TreeNode));
        (*iter)->down_calculated = false;
        (*iter)->up_calculated = false;
    }
    iter = tree->nodes;
    for (uint64_t i = 0; i < tree->n_nodes; ++i, ++iter) {
        double value;
        int64_t left, right;
        fscanf(fin, "%lf %ld %ld", &value, &left, &right);
        (*iter)->value = value;
        (*iter)->left = left >= 0 ? tree->nodes[left] : 0;
        (*iter)->right = right >= 0 ? tree->nodes[right] : 0;
    }
    tree->root = *tree->nodes;
    tree->root->down_calculated = true;
    tree->root->down_sum = tree->root->value;
    fclose(fin);
    return 0;
}

int tree_max_sum_down(struct Tree *tree, double *out) {
    if (!tree || !out) {
        return ERR_NULL_PTR;
    }
    if (!tree->n_nodes) {
        return ERR_EMPTY_TREE;
    }
    double max = tree->root->value;
    struct TreeNode **stack = malloc(sizeof(struct TreeNode*) * tree->n_nodes);
    struct TreeNode **stack_end = stack;
    *(stack_end++) = tree->root;
    for (; stack != stack_end;) {
        --stack_end;
        struct TreeNode *cur = *stack_end;
        if (cur->down_sum > max) {
            max = cur->down_sum;
        }
        if (cur->left) {
            if (!cur->left->down_calculated) {
                cur->left->down_calculated = true;
                cur->left->down_sum =
                    cur->down_sum + cur->left->value;
            }
            *(stack_end++) = cur->left;
        }
        if (cur->right) {
            if (!cur->right->down_calculated) {
                cur->right->down_calculated = true;
                cur->right->down_sum =
                    cur->down_sum + cur->right->value;
            }
            *(stack_end++) = cur->right;
        }
    }
    free(stack);
    *out = max;
    return 0;
}

int tree_max_sum_up(struct Tree *tree, double *out) {
    if (!tree || !out) {
        return ERR_NULL_PTR;
    }
    if (!tree->n_nodes) {
        return ERR_EMPTY_TREE;
    }
    return 0;
}

int tree_finalize(struct Tree *tree) {
    if (!tree) {
        return ERR_NULL_PTR;
    }
    struct TreeNode **iter = tree->nodes;
    for (uint64_t i = 0; i < tree->n_nodes; ++i, ++iter) {
        free(*iter);
    }
    free(tree->nodes);
    return 0;
}
