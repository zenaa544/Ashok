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

==============================================================
   ✅ Approach
Use a monotonic stack (using a string as a stack) to keep digits in increasing order. At each step:

Remove digits from the stack if the current digit is smaller than the stack's top and we still have k digits to remove.

Finally:

Remove remaining digits from the end if k > 0.

Remove leading zeros.

Return "0" if the resulting number is empty.

🧠 Time Complexity
O(n) where n = num.size()

string removeKdigits(string num, int k) {
    string result;

    for (char digit : num) {
        // Remove from result if digit < back of result and k > 0
        while (!result.empty() && k > 0 && result.back() > digit) {
            result.pop_back();
            k--;
        }
        result.push_back(digit);
    }

    // If still need to remove digits, remove from end
    while (k > 0 && !result.empty()) {
        result.pop_back();
        k--;
    }

    // Remove leading zeros
    int i = 0;
    while (i < result.size() && result[i] == '0') i++;

    result = result.substr(i);

    return result.empty() ? "0" : result;
}

