import typing
import collections

class TreeNode:
    def __init__(self):
        """_summary_
        """
        self.value: float = 0
        self.left: TreeNode = None
        self.right: TreeNode = None
        self.visited: bool = False
        self.down_calculated: bool = False
        self.down_sum: float = 0
        self.up_calculated: bool = False
        self.up_sum: float = 0

class Tree:
    def __init__(self, fn: str):
        """_summary_

        Args:
            fn (str): _description_
        """
        minimum = 0
        with open(fn, "r") as fin:
            n_nodes: int = int(fin.readline())
            self.nodes: typing.List[TreeNode] =\
                [TreeNode() for i in range(n_nodes)]
            for i in self.nodes:
                tokens = fin.readline().split()
                i.value = float(tokens[0])
                if (not minimum or i.value < minimum):
                    minimum = i.value
                i.left =\
                    self.nodes[int(tokens[1])] if int(tokens[1]) >= 0 else None
                i.right =\
                    self.nodes[int(tokens[2])] if int(tokens[2]) >= 0 else None
        self.root: TreeNode = self.nodes[0]
        self.root.down_calculated = True
        self.root.down_sum = self.root.value
        self.n_inf: float = n_nodes * minimum if minimum < 0 else -1
    def max_sum_down(self):
        """_summary_
        """
        if (not len(self.nodes)):
            raise Exception("EMPTY_TREE")
        stack: collections.deque[TreeNode] = collections.deque()
        out: float = self.root.down_sum
        stack.append(self.root)
        while (len(stack)):
            cur = stack.pop()
            if (cur.down_sum > out):
                out = cur.down_sum
            if (cur.left):
                if (not cur.left.down_calculated):
                    cur.left.down_calculated = True
                    cur.left.down_sum = cur.down_sum + cur.left.value
                stack.append(cur.left)
            if (cur.right):
                if (not cur.right.down_calculated):
                    cur.right.down_calculated = True
                    cur.right.down_sum = cur.down_sum + cur.right.value
                stack.append(cur.right)
        return out
