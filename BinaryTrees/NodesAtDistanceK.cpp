Problem statement
You are given an arbitrary binary tree, a node of the tree, and an integer 'K'. You need to find all such nodes which have a distance K from the given node and return the list of these nodes.



Distance between two nodes in a binary tree is defined as the number of connections/edges in the path between the two nodes.



Note:

1. A binary tree is a tree in which each node has at most two children. 
2. The given tree will be non-empty.
3. The given tree can have multiple nodes with the same value.
4. If there are no nodes in the tree which are at distance = K from the given node, return an empty list.
5. You can return the list of values of valid nodes in any order. For example if the valid nodes have values 1,2,3, then you can return {1,2,3} or {3,1,2} etc.



  void markParents(BinaryTreeNode<int>* root, unordered_map<BinaryTreeNode<int>*, BinaryTreeNode<int>*>& parentMap) {
    queue<BinaryTreeNode<int>*> q;
    q.push(root);

    while (!q.empty()) {
        auto curr = q.front(); q.pop();
        if (curr->left) {
            parentMap[curr->left] = curr;
            q.push(curr->left);
        }
        if (curr->right) {
            parentMap[curr->right] = curr;
            q.push(curr->right);
        }
    }
}

vector<BinaryTreeNode<int>*> printNodesAtDistanceK(BinaryTreeNode<int>* root, BinaryTreeNode<int>* target, int K) {
    // Write your code here.
    unordered_map<BinaryTreeNode<int>*, BinaryTreeNode<int>*> parentMap;
    markParents(root, parentMap);

    unordered_set<BinaryTreeNode<int>*> visited;
    queue<BinaryTreeNode<int>*> q;
    q.push(target);
    visited.insert(target); // to avoid visiting again from child to parent and then child node

    int currDist = 0;

    while (!q.empty()) {
       if (currDist == K) {
         break;
       }

        int currenLevelSize = q.size();       
        currDist++;

        for (int i = 0; i < currenLevelsize; ++i) {
            auto node = q.front();
             q.pop();
            
            if (node->left && !visited.count(node->left)) {
                q.push(node->left);
                visited.insert(node->left);
            }
            if (node->right && !visited.count(node->right)) {
                q.push(node->right);
                visited.insert(node->right);
            }
            if (parentMap.contains(node) && !visited.count(parentMap[node])) {
                q.push(parentMap[node]);
                visited.insert(parentMap[node]);
            }
        }
    }

    vector<BinaryTreeNode<int>*> result;
    while (!q.empty()) {
        result.push_back(q.front());
        q.pop();
    }
    return result;
}
