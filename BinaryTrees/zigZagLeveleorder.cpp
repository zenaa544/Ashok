class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    //vector<int> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>result;
        //vector<int>result;
        if(root==NULL) return result;
        bool leftToRight=true;
        
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
         int size= q.size();
         vector<int>row(size);
         for(int i=0;i<size;i++){
            TreeNode* node =q.front();
            q.pop();
            if(node->left)q.push(node->left);
            if(node->right)q.push(node->right);
            int index;
            if(leftToRight==true){
                 index=i;
            }
            else
                 index = size-1-i;
            
            row[index]=node->val;
         }
            leftToRight=!leftToRight;
            result.push_back(row);
            /*IF single vestor be returned
              for(auto val:row){
              result.push_back(val)
              }*/
        }
        
       return result; 
    }
};
