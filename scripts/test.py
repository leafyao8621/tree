import tree.cpp
import tree.c
import tree.native

if __name__ == "__main__":
    print("CPP")
    tree.cpp.run("in/test.tree", 10, verbose=True)
    print("C")
    tree.c.run("in/test.tree", 10, verbose=True)
    print("NATIVE")
    tree.native.run("in/test.tree", 10, verbose=True)
