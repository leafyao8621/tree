#include "core/core.h"
#include <iostream>

int main() {
    try {
        Core::Tree tree("../../../scripts/in/test.tree");
        for (int i = 0; i < 10; ++i) {
            std::cout << "iter: " << i <<
            " max_down: " << tree.max_sum_down() << '\n';
        }
    } catch (Core::Tree::Err e) {
        switch (e) {
        case Core::Tree::Err::FILE_ACCESS:
            std::cout << "FILE_ACCESS\n";
            break;
        case Core::Tree::Err::EMPTY_TREE:
            std::cout << "EMPTY_TREE\n";
            break;
        }
    }

    return 0;
}
