#include <stdio.h>
#include "core/core.h"

int main(void) {
    struct Tree tree;
    int ret = tree_initialize(&tree, "../../../scripts/in/test.tree");
    if (ret) {
        goto cleanup;
    }
    double max_up = 0;
    double max_down = 0;
    for (int i = 0; i < 10; ++i) {
        ret = tree_max_sum_down(&tree, &max_down);
        printf("iter: %d max_down: %lf\n", i, max_down);
        if (ret) {
            goto cleanup;
        }
    }
    for (int i = 0; i < 10; ++i) {
        ret = tree_max_sum_up(&tree, &max_up);
        printf("iter: %d max_up: %lf\n", i, max_up);
        if (ret) {
            goto cleanup;
        }
    }
cleanup:
    switch (ret) {
    case ERR_NULL_PTR:
        puts("ERR_NULL_PTR");
        break;
    case ERR_FILE_ACCESS:
        puts("ERR_FILE_ACCESS");
        break;
    }
    tree_finalize(&tree);
    return 0;
}
