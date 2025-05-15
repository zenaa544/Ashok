662. Maximum Width of Binary Tree

Given the root of a binary tree, return the maximum width of the given tree.
The maximum width of a tree is the maximum width among all levels.
The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
It is guaranteed that the answer will in the range of a 32-bit signed integer.

Example 1:
Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).
Example 2

Input: root = [1,3,2,5,null,null,9,6,null,7]
Output: 7
Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7).
Example 3:
Input: root = [1,3,2,5]
Output: 2
Explanation: The maximum width exists in the second level with length 2 (3,2).

Understanding the Position Numbering (2p + 1 and 2p + 2)
When we work with binary trees, we can assign positions to nodes in a way that represents their location in a complete binary tree.
 This numbering system has important properties:
Root is at position 0
For any node at position p:

Its left child is at position 2*p + 1
Its right child is at position 2*p + 2

This creates a consistent numbering system where:

Level 0: The root is at position 0
Level 1: Left child at 1, right child at 2
Level 2: Children of node 1 are at 3 and 4, children of node 2 are at 5 and 6
And so on...

      0              Level 0
    /   \
   1     2           Level 1
  / \   / \
 3   4 5   6         Level 2
The position of a node tells us exactly where it sits in the complete binary tree structure, even if some nodes are missing. This is critical for calculating width correctly.

 - Why Subtract position - levelStart?
Subtracting position - levelStart (the position of the first node at the current level) is an optimization to prevent integer overflow.
As we go deeper in the tree, the position values grow exponentially:

At level 0: positions are around 0
At level 1: positions are around 1-2
At level 2: positions are around 3-6
At level 3: positions are around 7-14
...
At level 32: positions could exceed the range of a 64-bit integer!

By normalizing positions relative to the start of each level, we keep the numbers manageable even for deep trees.

 
  =========================================================
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        
        // We'll use unsigned long long to prevent integer overflow
        // as we calculate position indices
        using ull = unsigned long long;
        
        // Maximum width found so far
        ull maxWidth = 0;
        
        // Queue for level order traversal
        // Each entry contains {node, position}
        queue<pair<TreeNode*, ull>> q;
        
        // Start with root at position 0
        q.push({root, 0});
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            // Get the position of the leftmost node at this level
            ull levelStart = q.front().second;
            
            // Variables to track the leftmost and rightmost nodes
            ull left = 0, right = 0;
            
            // Process all nodes at the current level
            for (int i = 0; i < levelSize; i++) {
                // Get current node and its position
                TreeNode* node = q.front().first;
                ull position = q.front().second;
                q.pop();
                
                // For the first node in level, record its position as leftmost
                if (i == 0) left = position;
                
                // For the last node in level, record its position as rightmost
                if (i == levelSize - 1) right = position;
                
                // Calculate positions for children
                // Left child is at 2*pos + 1
                // Right child is at 2*pos + 2
                // This maintains the complete binary tree numbering
                
                // Calculate position relative to level start to prevent overflow
                ull adjustedPos = position - levelStart;
                
                if (node->left) {
                    q.push({node->left, 2 * adjustedPos + 1}); // or we cand do push({node->left, (2 * width + 1) - levelStartWidth}); which is more undestandbale
                }
                
                if (node->right) {
                    q.push({node->right, 2 * adjustedPos + 2});
                }
            }
            
            // Update maximum width
            // Width is the difference between rightmost and leftmost positions + 1
            maxWidth = max(maxWidth, right - left + 1);
        }
        
        return maxWidth;
    }
};
  
