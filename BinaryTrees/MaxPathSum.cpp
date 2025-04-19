/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxSum(TreeNode* root, int& maxS){

       if(root==NULL)return 0;

       int leftSum=maxSum(root->left,maxS);
       int rightSum=maxSum(root->right,maxS);

       //don't take negative values.take 0 instead to maximize the sum
       leftSum=leftSum<0?0:leftSum;
       rightSum=rightSum<0?0:rightSum;

       int sum = leftSum+rightSum+root->val;

       maxS=max(sum,maxS);

       return max(leftSum,rightSum)+root->val;

    }
    int maxPathSum(TreeNode* root) {
        
        if (root==NULL)return 0;
        int maxS = INT_MIN;
        maxSum(root,maxS);
        return maxS;
    }
};
