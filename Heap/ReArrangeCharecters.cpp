Given a string s with repeated characters, the task is to rearrange characters in a string such that no two adjacent characters are the same.
Note: The string has only lowercase English alphabets and it can have multiple solutions. Return any one of them. If there is no possible solution, 
then print empty string ("").

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
==============================================================================================================

Alternate method only for lower case charecters
Case	Best Approach
You want best general-purpose correctness	✅ Use Heap
You want fast, simple code for lowercase a–z	✅ Use Greedy Fill
You want to support Unicode or multicharacter sets	✅ Use Heap

This method is faster (O(n + k log k), where k = 26) and uses less memory than a heap.

It works well due to limited alphabet size (only lowercase letters).

It doesn’t truly use two classic “pointers” but simulates them via the even/odd index fill pattern.


🧠 Idea:
Sort characters by frequency.

Greedily place characters in alternate indices to avoid adjacency.

Use two passes:

Fill even indices (0, 2, 4, …) first.

Then fill odd indices (1, 3, 5, …).



class Solution {
  public:
    string rearrangeString(string s) {
        // code here
        
      vector<int> freq(26, 0);
    int n = s.size();

    for (char c : s)
        freq[c - 'a']++;

    int maxFreq = *max_element(freq.begin(), freq.end());
    if (maxFreq > (n + 1) / 2) return ""; // Not possible

    // Create sorted character list based on frequency
    vector<pair<int, char>> sortedChars;
    for (int i = 0; i < 26; ++i) {
        if (freq[i])
            sortedChars.push_back({freq[i], (char)(i + 'a')});
    }

    sort(sortedChars.rbegin(), sortedChars.rend()); // sort by freq descending

    string res(n, ' ');
    int idx = 0; // even index start

  for (auto& p : sortedChars) {
    int count = p.first;
    char ch = p.second;

    while (count-- > 0) {
        res[idx] = ch;
        idx += 2;
        if (idx >= n) idx = 1;
    }
}

    return res;
    }
};
