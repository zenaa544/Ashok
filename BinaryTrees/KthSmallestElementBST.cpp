int inorder(BinaryTreeNode<int>* root, int k, int& count){
    if(!root) return -1;

    int result= inorder(root->left,k,count);
    if(result!=-1)return result;
    
    count++;
      
    if(count==k)
        return root->data;
    else
      return inorder(root->right,k,count);
}
int kthSmallest(BinaryTreeNode<int>* root, int k) {
    // Write your code here.
    if(!root || k==0)return -1;
    
    int count=0;
    return inorder(root,k,count);


}
