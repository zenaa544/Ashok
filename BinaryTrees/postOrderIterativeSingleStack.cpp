//{ Driver Code Starts
//Initial Template for C++


#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000

// Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Utility function to create a new Tree Node
Node* newNode(int val) {
    Node* temp = new Node;
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}


// Function to Build Tree
Node* buildTree(string str) {
    // Corner Case
    if (str.length() == 0 || str[0] == 'N') return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;) ip.push_back(str);

    // Create the root of the tree
    Node* root = newNode(stoi(ip[0]));

    // Push the root to the queue
    queue<Node*> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while (!queue.empty() && i < ip.size()) {

        // Get and remove the front of the queue
        Node* currNode = queue.front();
        queue.pop();

        // Get the current node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if (currVal != "N") {

            // Create the left child for the current node
            currNode->left = newNode(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size()) break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N") {

            // Create the right child for the current node
            currNode->right = newNode(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}


// } Driver Code Ends

// User function Template for C++

/* Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
};*/
class Solution{
    public:
/*Algorithm:
1-Use a stack and push the root node.

2-Use a pointer lastVisited to track the last visited node.

3-Traverse to the leftmost node while pushing nodes onto the stack.

4-If the current node has no right child or the right child is already visited, visit the node (pop and print).

5-Otherwise, move to the right subtree.

6-Repeat until all nodes are visited.
*/
    vector<int> postOrder(Node* node) {
        
        vector<int> postOrder;
        if (node == nullptr) return postOrder;

        stack<Node*> st;
        Node* curr = node;
        Node* lastVisited = nullptr;
    
        

        while (!st.empty() || curr != nullptr) {
            if (curr != nullptr) {
                st.push(curr);
                curr = curr->left;  // Move to left child
            } else {
                Node* topNode = st.top();
                // If right child exists and is not visited yet, move to right child
                if (topNode->right != nullptr && topNode->right != lastVisited) {
                    curr = topNode->right;
                } else {
                    // Visit node
                    postOrder.push_back(topNode->data);
                    lastVisited = topNode;
                    st.pop();
                }
            }
        }
       return postOrder; 
    }
};


//{ Driver Code Starts.

/* Driver program to test size function*/

  

int main() {

   
    int t;
    scanf("%d ", &t);
    while (t--) {
        string s, ch;
        getline(cin, s);
        
        Node* root = buildTree(s);

        vector<int> ans;
        Solution ob;
        ans = ob.postOrder(root) ;

        for (int i = 0; i < ans.size(); i++)
            cout << ans[i] << " ";

        cout << endl;
     
    
cout << "~" << "\n";
}
    return 0;
}

// } Driver Code Ends
