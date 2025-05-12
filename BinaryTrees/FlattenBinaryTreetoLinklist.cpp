Given the root of a binary tree, flatten the tree into a "linked list":

The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
The "linked list" should be in the same order as a pre-order traversal of the binary tree.


  class Solution {
public:
    TreeNode* helper(TreeNode* root){

        if(root==nullptr)return nullptr;
        
        TreeNode* left=helper(root->left);
        TreeNode* right= helper( root->right);
        root->left=nullptr;
        root->right=nullptr;
        //TreeNode* current = left;
        if(left){
            TreeNode* current = left;
            while(current!=nullptr && current->right){
                current=current->right;
            }
             current->right=right;
             root->right=left;
        }
        else{
            root->right=right;
        }
               
       return root;

    }
    void flatten(TreeNode* root) {

        if(!root)return;
        
         helper(root);

        
    }
};
