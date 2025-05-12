TreeNode<int>* constructTree(int start, int end,int& postIndex,vector<int>& postOrder, vector<int>& inOrder,unordered_map<int,int>& inIndexMap){

     if(start==end){
          return new TreeNode<int>(postOrder[postIndex--]);
     }
     if(start>end)return NULL;

     TreeNode<int>* root = new TreeNode<int>(postOrder[postIndex]);
     int inIndex= inIndexMap[postOrder[postIndex]];
     postIndex--;
     
     root->right=constructTree(inIndex+1,end,postIndex,postOrder,inOrder,inIndexMap);
     root->left=constructTree(start,inIndex-1,postIndex,postOrder,inOrder,inIndexMap);

     
     return root;

}
TreeNode<int>* getTreeFromPostorderAndInorder(vector<int>& postOrder, vector<int>& inOrder){
	// Write your code here.
     int startI=0;
     int endI=inOrder.size()-1;
     int postI=endI;
     unordered_map<int,int> inIndexMap;
     for(int i=0;i<inOrder.size();i++){
          inIndexMap[inOrder[i]]=i;
     }
     return constructTree(startI,endI,postI,postOrder,inOrder,inIndexMap);
}
