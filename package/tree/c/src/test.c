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
    ret = tree_max_sum_down(&tree, &max_down);
    if (ret) {
        goto cleanup;
    }
    for (int i = 0; i < 10; ++i) {
        printf("iter: %d max_down: %lf\n", i, max_down);
        ret = tree_max_sum_down(&tree, &max_down);
        if (ret) {
            goto cleanup;
        }
    }
    printf("max_up: %lf\n", max_up);
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
