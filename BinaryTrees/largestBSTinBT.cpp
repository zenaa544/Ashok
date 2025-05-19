Problem statement
You have been given a Binary Tree of 'N' nodes, where the nodes have integer values. 
Your task is to return the size of the largest subtree of the binary tree which is also a BST.

A binary search tree (BST) is a binary tree data structure which has the following properties.

• The left subtree of a node contains only nodes with data less than the node’s data.
• The right subtree of a node contains only nodes with data greater than the node’s data.
• Both the left and right subtrees must also be binary search trees.


**********************************************************************
✅ Approach: Bottom-Up Traversal (Postorder)
We traverse the tree in post-order and at each node, gather information:

Whether the left and right subtrees are BSTs

Min and max values in left/right subtrees

Size of the current subtree if it's a BST

🧠 Key Idea
For each node, return:

isBST: Is the subtree rooted at this node a BST?

size: Size of the subtree if it is a BST

minVal: Minimum value in subtree

maxVal: Maximum value in subtree

***********************************************************************


struct Info {
    bool isBST;
    int size;
    int minVal;
    int maxVal;
    Info(bool isB, int s, int minV, int maxV) :
        isBST(isB), size(s), minVal(minV), maxVal(maxV) {}
};
int maxBSTSize = 0;
Info largestBSTUtil(TreeNode* root){
     
     if(!root) return Info(true,0,INT_MAX,INT_MIN);

     Info left = largestBSTUtil(root->left);
     Info right = largestBSTUtil(root->right);
     
     
     if(left.isBST && right.isBST && root->data>left.maxVal && root->data<right.minVal){
         int currSize = left.size + right.size + 1;
          maxBSTSize = max(maxBSTSize, currSize);
          return Info(true,
                    currSize,
                    min(root->data, left.minVal),
                    max(root->data, right.maxVal));
     }

     return Info(false, 0, 0, 0);

}
int largestBST(TreeNode * root){
    // Write your code here.
     maxBSTSize = 0;
    largestBSTUtil(root);
    return maxBSTSize;
}
