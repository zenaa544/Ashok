Problem statement
You have a binary tree of 'N' unique nodes and a Start node from where the tree will start to burn. Given that the Start node will always exist in the tree, your task is to print the time (in minutes) that it will take to burn the whole tree.



It is given that it takes 1 minute for the fire to travel from the burning node to its adjacent node and burn down the adjacent node.

#include <bits/stdc++.h>

using namespace std;

template <typename T>
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

// Build parent map and get pointer to start node
TreeNode<int>* mapParents(TreeNode<int>* root,
                          unordered_map<TreeNode<int>*, TreeNode<int>*>& parent,
                          int start) {
    queue<TreeNode<int>*> q;
    q.push(root);
    TreeNode<int>* startNode = nullptr;

    while (!q.empty()) {
        TreeNode<int>* curr = q.front(); q.pop();
        if (curr->data == start) {
            startNode = curr;
        }

        if (curr->left) {
            parent[curr->left] = curr;
            q.push(curr->left);
        }
        if (curr->right) {
            parent[curr->right] = curr;
            q.push(curr->right);
        }
    }

    return startNode;
}

int timeToBurnTree(TreeNode<int>* root, int start) {
    if (!root) return 0;

    unordered_map<TreeNode<int>*, TreeNode<int>*> parentMap;
    TreeNode<int>* startNode = mapParents(root, parentMap, start);

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

            if (node->left && visited.insert(node->left).second) {
                q.push(node->left);
                burned = true;
            }

            if (node->right && visited.insert(node->right).second) {
                q.push(node->right);
                burned = true;
            }

            if (parentMap.count(node) && visited.insert(parentMap[node]).second) {
                q.push(parentMap[node]);
                burned = true;
            }
        }

        if (burned) time++;
    }

    return time;
}
