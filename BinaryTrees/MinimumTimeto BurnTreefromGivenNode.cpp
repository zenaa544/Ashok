Problem statement
You have a binary tree of 'N' unique nodes and a Start node from where the tree will start to burn. Given that the Start node will always exist in the tree, your task is to print the time (in minutes) that it will take to burn the whole tree.



It is given that it takes 1 minute for the fire to travel from the burning node to its adjacent node and burn down the adjacent node.

#include <bits/stdc++.h>
using namespace std;

template<typename T>
class TreeNode {
public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode(T val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Step 1: Build parent map
void mapParents(TreeNode<int>* root, unordered_map<TreeNode<int>*, TreeNode<int>*>& parent) {
    queue<TreeNode<int>*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode<int>* curr = q.front(); q.pop();
        if (curr->left) {
            parent[curr->left] = curr;
            q.push(curr->left);
        }
        if (curr->right) {
            parent[curr->right] = curr;
            q.push(curr->right);
        }
    }
}

// Step 2: Find the start node
TreeNode<int>* findStart(TreeNode<int>* root, int start) {
    if (!root) return nullptr;
    if (root->data == start) return root;

    TreeNode<int>* left = findStart(root->left, start);
    if (left) return left;

    return findStart(root->right, start);
}

// Step 3: BFS to simulate fire spreading
int timeToBurnTree(TreeNode<int>* root, int start) {
    if (!root) return 0;

    unordered_map<TreeNode<int>*, TreeNode<int>*> parentMap;
    mapParents(root, parentMap);

    TreeNode<int>* startNode = findStart(root, start);

    unordered_set<TreeNode<int>*> visited;
    queue<TreeNode<int>*> q;
    q.push(startNode);
    visited.insert(startNode);

    int time = 0;

    while (!q.empty()) {
        int size = q.size();
        bool burned = false;

        for (int i = 0; i < size; ++i) {
            TreeNode<int>* node = q.front(); q.pop();

            // Spread to left
            if (node->left && !visited.count(node->left)) {
                visited.insert(node->left);
                q.push(node->left);
                burned = true;
            }

            // Spread to right
            if (node->right && !visited.count(node->right)) {
                visited.insert(node->right);
                q.push(node->right);
                burned = true;
            }

            // Spread to parent
            if (parentMap.count(node) && !visited.count(parentMap[node])) {
                visited.insert(parentMap[node]);
                q.push(parentMap[node]);
                burned = true;
            }
        }

        if (burned)
            time++;  // Fire spread in this round
    }

    return time;
}
