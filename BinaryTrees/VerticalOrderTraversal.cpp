**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
/*
    vector<vector<int>> verticalTraversal(TreeNode* root) {

    
       vector<vector<int>> result;
        map<int, map<int,multiset<int>>> mp;
       if(root==NULL) return result;

       queue<pair<TreeNode*, pair<int,int>>> q;

       q.push({root,{0,0}});
       while(!q.empty()){
        
        auto entry = q.front();
        q.pop();
        TreeNode* node = entry.first;
        int vert= entry.second.first;
        int level= entry.second.second;
        mp[vert][level].insert(node->val);

        if(node->left) 
            q.push({node->left,{vert-1, level+1}});
        if(node->right)
            q.push({node->right,{vert+1,level+1}});    

       }
       
       for(auto entry: mp){
         vector<int> col;
         for(auto q : entry.second){
            col.insert(col.end(),q.second.begin(),q.second.end());
         }
         result.emplace_back(col);
       }
       return result;
       }*/
        vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int, vector<pair<int, int>>> nodes; // col -> vector of (row, val)
        queue<tuple<TreeNode*, int, int>> q;    // node, row, col

        q.push({root, 0, 0});

        while (!q.empty()) {
            auto [node, row, col] = q.front();
            q.pop();

            nodes[col].emplace_back(row, node->val);

            if (node->left)  q.push({node->left,  row + 1, col - 1});
            if (node->right) q.push({node->right, row + 1, col + 1});
        }

        vector<vector<int>> result;
        for (auto& [col, vec] : nodes) {
            sort(vec.begin(), vec.end()); // sort by (row, value)
            vector<int> colVals;
            for (auto& [row, val] : vec)
                colVals.push_back(val);
            result.push_back(colVals);
        }

        return result;
    
    }
};

=============EVEN SIMPLER

    vector<int> verticalOrderTraversal(TreeNode<int> *root)
{
    //    Write your code here.

        map<int, vector<int>> nodes; // col -> vector of (row, val)
        queue<tuple<TreeNode<int>*, int>> q;    // node, row, col

        q.push({root, 0});

        while (!q.empty()) {
            auto [node, col] = q.front();
            q.pop();

            nodes[col].emplace_back(node->data);

            if (node->left)  q.push({node->left, col - 1});
            if (node->right) q.push({node->right, col + 1});
        }

        vector<int> result;
        for (auto& [col, vec] : nodes) {
            //sort(vec.begin(), vec.end()); // sort by (row, value)
            //vector<int> colVals;
            for (auto& val : vec)
                result.push_back(val);
        }

        return result;
    
    
}
