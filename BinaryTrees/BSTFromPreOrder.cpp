/************
Use max , to check if a node is less than the root;

***********************/  

TreeNode* insertNode(vector<int>& preOrder,int& index,int max){
    
    if(index>=preOrder.size() || preOrder[index]>max)
       return NULL;
    TreeNode* root = NULL;  
        
    root = new TreeNode(preOrder[index]); 
    
    index++;
    root->left=insertNode(preOrder,index,root->data);
    root->right=insertNode(preOrder,index,max);
    
    return root;    

}
TreeNode *preOrderTree(vector<int> &preOrder)
{
    // Write your code here.
    int index=0;
    return insertNode(preOrder,index,INT_MAX);
}
