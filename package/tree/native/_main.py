from ._core import Tree

def run(fn: str, iter: int, verbose: bool=False):
    """_summary_

    Args:
        fn (str): _description_
        iter (int): _description_
        verbose (bool, optional): _description_. Defaults to False.
    """
    tree: Tree = Tree(fn)
    for i in range(iter):
        max_down: float = tree.max_sum_down()
        if (verbose):
            print(f"iter: {i} max_down: {max_down}")
