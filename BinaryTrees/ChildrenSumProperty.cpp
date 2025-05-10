Problem statement
Given a binary tree of nodes 'N', you need to modify the value of its nodes, such that the tree holds the Children sum property.

A binary tree is said to follow the children sum property if, for every node of that tree, the value of that node is equal to the sum of the value(s) of all of its children nodes( left child and the right child).

Note :
 1. You can only increment the value of the nodes, in other words, the modified value must be at least equal to the original value of that node.
 2. You can not change the structure of the original binary tree.
 3. A binary tree is a tree in which each node has at most two children.      
 4. You can assume the value can be 0 for a NULL node and there can also be an empty tree.
Detailed explanation ( Input/output format, Notes, Images )



=====================================================================
void incrementChild(BinaryTreeNode < int > * root, int diff){
       if(root==NULL || root->left==NULL && root->right==NULL)
        return;
       
       
       if(root->left){
            root->left->data+=diff;
            incrementChild(root->left,diff);
       }
       else {
            root->right->data+=diff;
            incrementChild(root->right,diff);
       }
      return;           
}
void changeTree(BinaryTreeNode < int > * root) {
    // Write your code here.
    if(root==NULL || root->left==NULL && root->right==NULL)
        return;

    changeTree(root->left);
    changeTree(root->right);

    int leftData= root->left?root->left->data:0;
    int rightData=root->right?root->right->data:0;

    int childSum= leftData+rightData;

    if(root->data <= childSum)
        root->data=childSum;     
    else
        incrementChild(root,root->data-childSum);
    
    return;    
}  
