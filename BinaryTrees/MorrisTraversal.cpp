void morrisPreOrder(Node* root) {
    Node* current = root;

    while (current != nullptr) {
        if (current->left == nullptr) {
            cout << current->data << " ";
            current = current->right;
        } else {
            Node* predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current) {
                predecessor = predecessor->right;
            }

            if (predecessor->right == nullptr) {
                cout << current->data << " ";
                predecessor->right = current;
                current = current->left;
            } else {
                predecessor->right = nullptr;
                current = current->right;
            }
        }
    }
}

=====================================

  void morrisInOrder(Node* root) {
    Node* current = root;

    while (current != nullptr) {
        if (current->left == nullptr) {
            cout << current->data << " ";
            current = current->right;
        } else {
            // Find the inorder predecessor of current
            Node* predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current) {
                predecessor = predecessor->right;
            }

            if (predecessor->right == nullptr) {
                // Make current the right child of its inorder predecessor
                predecessor->right = current;
                current = current->left;
            } else {
                // Revert the changes made (i.e., fix the right child of predecessor)
                predecessor->right = nullptr;
                cout << current->data << " ";
                current = current->right;
            }
        }
    }
}
