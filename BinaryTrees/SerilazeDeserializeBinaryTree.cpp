
Problem statement
You have been given a binary tree of integers. You are supposed to serialize and deserialize (refer to notes) the given binary tree.

You can choose any algorithm to serialize/deserialize the given binary tree. 
You only have to ensure that the serialized string can be deserialized to the original binary tree.

Note :
Serialization is the process of translating a data structure or object state into a format that can be stored or transmitted
(for example, across a computer network) and reconstructed later. The opposite operation, that is, extracting a data structure
from stored information, is deserialization.

*********************************************************/
#include<bits/stdc++.h>
/*void serializePreOrder(string& s, TreeNode<int>* root){

   if(!root){
       s.append("-1,");
       return;
   }
   
   s.append(to_string(root->data)+',');

   serializePreOrder(s,root->left);
   serializePreOrder(s,root->right);
}*/
void serializePreOrder(TreeNode<int>* root, stringstream& ss) {
    if (!root) {
        ss << "-1,";
        return;
    }

    ss << root->data << ",";
    serializePreOrder(root->left, ss);
    serializePreOrder(root->right, ss);
}
string serializeTree(TreeNode<int> *root)
{
 //    Write your code here for serializing the tree
   /*
    string s="";
    serializePreOrder(s,root);

    return s;
    */
    stringstream ss;
    serializePreOrder(root, ss);
    return ss.str();
}
TreeNode<int>* buildTreePreOrder(stringstream& ss){
    string token;
    if (!getline(ss, token, ',')) return nullptr;

    if (token == "-1") return nullptr;

    TreeNode<int>* node = new TreeNode<int>(stoi(token));
    node->left = buildTreePreOrder(ss);
    node->right = buildTreePreOrder(ss);
    return node;
}
TreeNode<int>* deserializeTree(string &serialized)
{
 //    Write your code here for deserializing the tree
    if (serialized.empty()) return nullptr;

    stringstream ss(serialized);
    return buildTreePreOrder(ss);
}
