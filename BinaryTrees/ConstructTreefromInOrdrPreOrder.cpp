class Solution {
public:
    TreeNode* buildTreeR(unordered_map<int,int>& mp, vector<int>& inorder, 
                     vector<int>& preorder, int& preIndex, int left, int right){
         if (left > right)
        return nullptr;

    int rootVal = preorder[preIndex];
    preIndex++;

    // create the root Node
    TreeNode *root = new TreeNode(rootVal);

    // find the index of Root element in the in-order array.
    int index = mp[rootVal];

    // Recursively create the left and right subtree.
    root->left = buildTreeR(mp,inorder, preorder, preIndex, left, index - 1);
    root->right = buildTreeR(mp,inorder, preorder, preIndex, index + 1, right);

    return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
       unordered_map<int, int> inMap;
        
        for(int i =0;i<inorder.size();i++){
            inMap[inorder[i]]=i;
        }
        
        int pI =0;
        TreeNode* root= buildTreeR(inMap,inorder,preorder,pI,0,preorder.size()-1);
        
        return root; 
    }
};
