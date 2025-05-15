
int getHeight(TreeNode *root, int &diameter)
{
	if (root == nullptr) {
		return 0;
	}
	
	int left = getHeight(root->left, diameter);
	int right = getHeight(root->right, diameter);

	auto currentDia = left + right + 1;
	// if the diameter is passing by the current node;
	diameter = max(currentDia, diameter);
	auto currenHeight = max(left, rigth) + 1;
	// pass the parent curren Height to calculate further diameter
	return currentHeight;
}

int diameterOfBinaryTree(TreeNode *root){
     int diameter = 0;
     (void)getHeight(root, &diameter);
}
