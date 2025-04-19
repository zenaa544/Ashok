/************************************************************

    Following is the Binary Tree node structure:

    template <typename T>
    class TreeNode
    {
    public:
        T data;
        TreeNode<T> *left;
        TreeNode<T> *right;

        TreeNode(T data)
        {
            this -> data = data;
            left = NULL;
            right = NULL;
        }

        ~TreeNode()
        {
            if(left)
                delete left;
            if(right)
                delete right;
        }
    };

************************************************************/
#include<bits/stdc++.h>
bool isLeaf(TreeNode<int>* root){
    if(!root->left && !root->right)return true;
    else return false;
}

void addLeftBoundary(TreeNode<int>* root, vector<int>& result){
    
    TreeNode<int>* current=root->left;
        
    while(current!=NULL){

        if(!isLeaf(current))
           result.push_back(current->data);
        if(current->left)
           current=current->left;
        else   
           current=current->right;
    }    

}

void addLeaves(TreeNode<int>* root, vector<int>& result){

     if(isLeaf(root)){
        result.push_back(root->data);
        return;
     }
     if(root->left)addLeaves(root->left,result);
     if(root->right)addLeaves(root->right,result);   
}

void addRightBoundary(TreeNode<int>* root,vector<int>& result){

    TreeNode<int>* current= root->right;
    stack<int> st;
    while(current!=NULL){
        if(!isLeaf(current))
            st.push(current->data);
        if(current->right)
            current=current->right; 
        else
            current=current->left;       
    }

    while(!st.empty()){
        result.push_back(st.top());
        st.pop();
    }

}
vector<int> traverseBoundary(TreeNode<int> *root)
{
	// Write your code here.
    vector<int>result;
    if(!root)return result;
    if(!isLeaf(root)){
        result.push_back(root->data);
    }
    addLeftBoundary(root,result);
    addLeaves(root,result);
    addRightBoundary(root,result);
    return result;

}
