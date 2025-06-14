Given a string s with repeated characters, the task is to rearrange characters in a string such that no two adjacent characters are the same.
Note: The string has only lowercase English alphabets and it can have multiple solutions. Return any one of them. If there is no possible solution, then print empty string ("").

Examples:

Input : s = "aaabc"
Output: 1
Explanation: "aaabc" can rearranged to "abaca" or "acaba" as no two adjacent characters are same in the output string.
Input : s= "aaabb"
Output: 1
Explanation: "aaabb" can rearranged to "ababa" as no two adjacent characters are same in the output string.
Input : s = "aaaabc"
Output: 0
Explanation: No combinations possible such that two adjacent characters are different.


  ✅ Approach:
Count frequency of each character.

Use a max-heap (priority queue) to always pick the most frequent character.

Place characters alternatively while ensuring no two adjacent are the same.

If any character’s frequency is more than (s.size() + 1)/2, it's impossible.


  class Solution {
  public:
    string rearrangeString(string s) {
        // code here
        
      unordered_map<char,int> freq;
      
      for(char c :s){
          freq[c]++;
      }
       
      priority_queue<pair<int,char>> maxHeap;
      
      for(auto entry: freq){
          
          if(entry.second > (s.size()+1)/2)
            return "";
            
          maxHeap.push({entry.second,entry.first});   
      }
        
     string result="";
     pair<int,char> prev={0,'#'};
     while(!maxHeap.empty()){
         
         auto current=maxHeap.top();
         maxHeap.pop();
         
         result.push_back(current.second);
         
         if(prev.first>0)maxHeap.push(prev);
         
         current.first--;
         prev=current;
         
     }
     
     return result;
    }
};
