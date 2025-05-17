Node* insert(Node* root, int key) {
    if (root == nullptr) {
        // New node becomes a leaf
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    // If key == root->key, do nothing or handle duplicates based on your logic
    return root;
}
int main() {
    Node* root = nullptr;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};

    for (int key : keys) {
        root = insert(root, key);
    }

    cout << "Inorder Traversal of BST:\n";

    return 0;
}
========================================================

  Iterative
  =======================================================
  TreeNode<int>* insertAsLeaf(TreeNode<int>* root, int val) {
    if (!root) return new TreeNode<int>(val);  // If the tree is empty, create root

    TreeNode<int>* current = root;

    while (current) {
        // If current is a leaf (both children are null), break to insert
        if (!current->left && !current->right) break;

        // Traverse to the correct child based on BST rules
        if (val > current->val && current->right) {
            current = current->right;
        } else if (val < current->val && current->left) {
            current = current->left;
        } else {
            // If next move is null, we're at the parent of the leaf position
            break;
        }
    }

    // Insert new node as left or right child depending on value
    if (val > current->val)
        current->right = new TreeNode<int>(val);
    else
        current->left = new TreeNode<int>(val);

    return root;
}
