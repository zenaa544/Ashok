BinaryTreeNode<int> *successor(BinaryTreeNode<int> *root, BinaryTreeNode<int> *node,BinaryTreeNode<int>*& prev){

    if(!root)return NULL;
    
    BinaryTreeNode<int>* successorNode=successor(root->left,node,prev);
    if(!successorNode) {
        if(prev==node){
           return root;
        }
        else{
            prev=root;   
            return successor(root->right,node,prev);
        }
    }    
    else
        return successorNode;
}
BinaryTreeNode<int> *inorderSuccesor(BinaryTreeNode<int> *root, BinaryTreeNode<int> *node)
{  
    if(!root)return NULL;
    BinaryTreeNode<int> * prev=NULL;

    return successor(root,node,prev);

    


}
