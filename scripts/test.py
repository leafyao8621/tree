import tree.cpp
import tree.c

if __name__ == "__main__":
    print("CPP")
    tree.cpp.run("in/test.tree", 10, verbose=True)
    print("C")
    tree.c.run("in/test.tree", 10, verbose=True)
    # print("NATIVE")
    # print(tree.native.distance("../graph/test.graph", 0, 2, verbose=True))
