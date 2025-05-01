class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if(!root) return result;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
           int size=q.size();
           int rightNodeVal=-1;
           while(size--){
              TreeNode* node =q.front();
              q.pop();
              rightNodeVal= node->val;
              if(node->left)q.push(node->left);
              if(node->right)q.push(node->right);
           }
           if(rightNodeVal!=-1)
              result.push_back(rightNodeVal);

        }
     
    return result;
    }
};
