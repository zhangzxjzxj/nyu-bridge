Our implementation of the Binary Search Tree (from the discussion) is unbalanced.  Obviously, the down side to this is that we could, potentially, end up with searches that take O(n) time.  We would like to correct that and guarantee that searching will take O(Log n) time.  Create a tree class (and, of course, the TreeNode class) which makes sure that searching is always O(log n).  To do this, you should modify our solution so that it is either an AVL tree (or, for extra credit, a red-black tree).

You should also guarantee that insertions and removals are as close to O(log n) as possible (it can't be exactly, but will be closer to log n than to n.)

 

Prove your solution works by inserting random integers and printing them out in sorted, ascending, order.
