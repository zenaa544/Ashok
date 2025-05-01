Problem statement
You are given a Binary Tree of 'n' nodes.

The Top view of the binary tree is the set of nodes visible when we see the tree from the top.

Find the top view of the given binary tree, from left to right.

Example :
  
Input: Let the binary tree be:

                     1
                    /  \
                  2      3
                /  \      \
              4     5      6
                \         /
                 7       8
                /         \
              9            11
             /
           10
Output: [10, 4, 2, 1, 3, 6]

Explanation: Consider the vertical lines in the figure. The top view contains the topmost node from each vertical line.
  vector<int> getTopView(TreeNode<int> *root)
{
    // Write your code here.
    map<int,int> mp;
    queue<pair<TreeNode<int>*, int>> q;

    q.push({root,0});

    while(!q.empty()){
       
       auto [node, col]=q.front();
       q.pop();
       if(mp.find(col)==mp.end())
            mp[col]=node->data;
       if(node->left)q.push({node->left,col-1});
       if(node->right)q.push({node->right,col+1});     

    }

    vector<int> result;
    for(auto& [key,val]:mp){
        result.push_back(val);
    }
    return result;
}
