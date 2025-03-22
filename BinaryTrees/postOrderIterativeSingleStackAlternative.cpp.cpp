 vector<int> postOrder(Node* root) {
        
        vector<int> ans;
        if (root == nullptr) return ans;

        stack<Node*> st;
        
        Node* cur = root;
        //Node *temp =NULL;
        while (cur!=NULL || !st.empty()) {
            if(cur!=NULL){
                st.push(cur);
                cur=cur->left;
            }
            else {
                Node* temp=st.top()->right;
            
                if(temp==NULL){
                
                    temp= st.top();
                    st.pop();
                    ans.push_back(temp->data);
                
                
                    while(!st.empty() && temp==st.top()->right ){
                        temp=st.top();
                        st.pop();
                        ans.push_back(temp->data);
                    }
                }
                else{
                
                    cur=temp;
                }
            }
            
        }
            
        
        return ans;
    }
