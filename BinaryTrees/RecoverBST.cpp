Problem statement
You have been given a Binary Search Tree of 'N' nodes, where exactly two nodes of the same tree were swapped by mistake.
Your task is to restore or fix the BST, without changing its structure and return the root of the corrected BST.
Note:
Given BST will not contain duplicates.
*****************************************************************************************

In-order traversal of a BST gives a sorted sequence. If two nodes are swapped, the in-order traversal will show two violations:

First incorrect pair: first element > second element

Second incorrect pair: later, another first element > second element

We need to:

Do in-order traversal.

Identify the two nodes that are in the wrong position.

Swap their values.



*****************************************************************************************
void inorder(TreeNode* root, TreeNode* &first,TreeNode* &middle,TreeNode* &last,TreeNode* &prev){

    if(!root)return;

    inorder(root->left,first,middle,last,prev);

    if(prev && prev->data > root->data){

        if(!first){
            first=prev;
            middle=root;
        }
        else
          last=root;
    }
    prev=root;
    inorder(root->right,first,middle,last,prev);
}

TreeNode * FixBST(TreeNode * root){
    // Write your code here.
   
        TreeNode* first = nullptr;
        TreeNode* middle = nullptr;
        TreeNode* last = nullptr;
        TreeNode* prev = nullptr;

        inorder(root,first,middle,last,prev);

        if (first && last) {
            swap(first->data, last->data);
        } else if (first && middle) {
            swap(first->data, middle->data);
        }

        return root;
    

}
