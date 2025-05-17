bool isBSTUtil(BinaryTreeNode<int>* node, int min, int max){

      if(!node)return true;

      if(node->data<=min || node->data>=max)
        return false;

      return (isBSTUtil(node->left,min,node->data) && isBSTUtil(node->right,node->data,max))  ; 
}
bool validateBST(BinaryTreeNode<int>* root) 
{
    // Write your code here

    return isBSTUtil(root, INT_MIN, INT_MAX);
}
