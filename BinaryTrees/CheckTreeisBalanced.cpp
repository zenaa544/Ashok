int height(TreeNode<int>* root){
    if (root==NULL)return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if(leftHeight==-1 || rightHeight==-1 || abs(leftHeight-rightHeight)>1)
        return -1;

    return max(leftHeight,rightHeight)+1;

}

bool isBalancedBT(TreeNode<int>* root){
    // Write your code here.
    

    if(root==NULL)return true;

    int treeHeight=height(root);
    
    if(treeHeight==-1)return false;
    else return true;
}

int checkHeight(TreeNode *root, bool &isBalanced) 
{
    if (root == nullptr || !isBalanced)
        return 0;

    int left = checkHeight(root->left, isBalanced);
    int right = checkHeight(root->right, isBalanced);      
    if (std::abs(leftHeight - rightHeight) > 1) {
            isBalanced = false;
            return 0; // No need to calculate further
    }

    // pass the height to the parent.
    return max (left, right) + 1;
}



bool isBalancedTree(TreeNode* root) 
{
    bool isBalanced = true;

    checkHeight(root, isBalanced);

    return isBalalnced;
    
}
