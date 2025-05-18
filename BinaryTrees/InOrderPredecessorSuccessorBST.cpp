Problem statement
You have been given a binary search tree of integers with ‘N’ nodes. You are also given 'KEY' which represents data of a node of this tree.



Your task is to return the predecessor and successor of the given node in the BST.



Note:
1. The predecessor of a node in BST is that node that will be visited just before the given node in the inorder traversal of the tree. If the given node is visited first in the inorder traversal, then its predecessor is NULL.

2. The successor of a node in BST is that node that will be visited immediately after the given node in the inorder traversal of the tree. If the given node is visited last in the inorder traversal, then its successor is NULL.

3. The node for which the predecessor and successor will not always be present. If not present, you can hypothetically assume it's position (Given that it is a BST) and accordingly find out the predecessor and successor.

4. A binary search tree (BST) is a binary tree data structure which has the following properties.
     • The left subtree of a node contains only nodes with data less than the node’s data.
     • The right subtree of a node contains only nodes with data greater than the node’s data.
     • Both the left and right subtrees must also be binary search trees.




  Iterative

  pair<int, int> predecessorSuccessor(TreeNode *root, int key)
{
    // Write your code here.

    TreeNode* predecessor = NULL;
    TreeNode* successor = NULL;
    TreeNode* curr = root;

    while (curr) {
        
        if (curr->data == key) {
            // Find predecessor: max value in left subtree
            if (curr->left) {
                TreeNode* temp = curr->left;
                while (temp->right)
                    temp = temp->right;
                predecessor = temp;
            }

            // Find successor: min value in right subtree
            if (curr->right) {
                TreeNode* temp = curr->right;
                while (temp->left)
                    temp = temp->left;
                successor = temp;
            }
            break;
        }else if (key < curr->data) {
            successor = curr; // this node could be successor
            curr = curr->left;
        } else {
            predecessor = curr; // this node could be predecessor
            curr = curr->right;
        }
    }

    return {
        predecessor ? predecessor->data : -1,
        successor ? successor->data : -1
    };

}

=========================================

  Recursive


  void findPreSuc(TreeNode* root, TreeNode*& pre, TreeNode*& suc, int key) {
    if (!root) return;

    if (root->data == key) {
        // Find predecessor: max value in left subtree
        if (root->left) {
            TreeNode* temp = root->left;
            while (temp->right) temp = temp->right;
            pre = temp;
        }

        // Find successor: min value in right subtree
        if (root->right) {
            TreeNode* temp = root->right;
            while (temp->left) temp = temp->left;
            suc = temp;
        }
    }
    else if (key < root->data) {
        suc = root; // current node could be successor
        findPreSuc(root->left, pre, suc, key);
    }
    else {
        pre = root; // current node could be predecessor
        findPreSuc(root->right, pre, suc, key);
    }
}

std::pair<int, int> predecessorSuccessor(TreeNode* root, int key) {
    TreeNode* pre = nullptr;
    TreeNode* suc = nullptr;

    findPreSuc(root, pre, suc, key);

    int predVal = pre ? pre->data : -1;
    int succVal = suc ? suc->data : -1;

    return {predVal, succVal};
}
