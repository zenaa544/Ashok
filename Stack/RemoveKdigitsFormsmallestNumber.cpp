Problem statement
You are given a non-negative integer ‘num’ in the form of a string and provided with an integer ‘k’.

You need to find the smallest integer possible by removing exactly ‘k’ digits from ‘num.’

Note :
‘num’ does not have leading zeros except when ‘num’ equals zero.


Solution
   Remove the largest digits from left Side so that it can form smaller number.
   By pushing to stack and removing the last largest numbers till k==0.
  
   Track number of removed digits with k ,till k becomes 0.
   It can form smallest number if digits are in increasing order from left.
   
  if the given digits are already in increasing order then we need to remove the digits from end.
  in this case we might not have removed any digits while pushing into stack.so k is still >0;
  After removal the digits copy stack elements to result.
  Now the result is in reverse order.We need to reverse it.
  Now if there are any trailing 0s then remove them before we reverse the string.
  Reverse the result if its empty return "0".

    string removeKDigits(string num, int k) 
{
    // Write your code here.

    string ans="";
    if(k>=num.size()) return "0";
    stack<char> st;

    for(int i=0;i<num.size();i++){

        while(!st.empty()&& st.top()-'0'>num[i]-'0' && k){
            st.pop();
            k--;
        }
        st.push(num[i]);
    }
    
    while(k){
        st.pop();
        k--;
    }
    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }
 
    while(ans.size()&& ans.back()=='0'){
      
        ans.pop_back();
       
    }
    
    reverse(ans.begin(),ans.end());
    if(ans.size())return ans;
    else return "0";
   
}

  
