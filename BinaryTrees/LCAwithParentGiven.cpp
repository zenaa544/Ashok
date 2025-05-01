The node structure of a binary tree is modified such that each node has the reference to its parent node.

You are given two nodes: ‘N1’ and ‘N2’, of the above binary tree. Your task is to return the lowest common ancestor (LCA) of the given nodes.

Note:

Let ‘TREE’ be a binary tree. The lowest common ancestor of two nodes, ‘N1’ and ‘N2’, is defined as the lowest node in ‘TREE’ with ‘N1’ and ‘N2’ as descendants (where we allow a node to be a descendant of itself).
Detailed explanation ( Input/output format, Notes, Images )
Constraints :
1 <= T <= 100
1 <= N <= 10 ^ 4
1 <= DATA <= 10 ^ 4 
N1 != N2
N1 and N2 exist in the ‘TREE’.
The ‘TREE’ contains unique nodes.

Where ‘T’ is the number of test cases, ‘N’ is the number of nodes in the ‘TREE’, ‘DATA’ represents the value of the node, ‘N1’ and ‘N2’ represent the nodes of which LCA has to be found.


============================
BinaryTreeNode<int> *leastCommonAncestor(BinaryTreeNode<int> *n1, BinaryTreeNode<int> *n2)
{  
    // Write your code here.
      map<BinaryTreeNode<int> *,int> mp;

    BinaryTreeNode<int>* p1=n1;
    //mp[p1]=p1->data;
    while(p1!=NULL){
        
        mp[p1]=p1->data;
        p1=p1->parent;
    }
     BinaryTreeNode<int>* p2= n2;
    while(p2!=NULL){
         
        if(mp.find(p2)!=mp.end()){
            return p2;
        }
        p2=p2->parent;
    }

    return p2;
}
========================================

  ✅ Approach: Two Pointers (Parent Traversal)
Start two pointers at n1 and n2.

Move each pointer up to its parent at each step.

When a pointer reaches the root (NULL), reset it to the other node.

Eventually, both pointers will meet at the lowest common ancestor.


  BinaryTreeNode<int>* leastCommonAncestor(BinaryTreeNode<int>* n1, BinaryTreeNode<int>* n2) {
    BinaryTreeNode<int>* p1 = n1;
    BinaryTreeNode<int>* p2 = n2;

    while (p1 != p2) {
        p1 = (p1 == NULL) ? n2 : p1->parent;
        p2 = (p2 == NULL) ? n1 : p2->parent;
    }

    return p1;  // or p2, both are same here
}
