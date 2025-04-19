int height(TreeNode<int>* root, int& diameter){
    if (root==NULL)return 0;

    int leftHeight = height(root->left,diameter);
    int rightHeight = height(root->right,diameter);
    
    diameter= max(leftHeight+rightHeight,diameter);

    return max(leftHeight,rightHeight)+1;

}
int diameterOfBinaryTree(TreeNode<int> *root){
	// Write Your Code Here.

    if (root==NULL)return 0;

    int diameter=0;
    height(root,diameter);
    return diameter;
}
