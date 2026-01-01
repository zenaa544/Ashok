// Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
// Example 1:

// Input: nums = [1,1,1,2,2,3], k = 2

// Output: [1,2]

// Example 2:

// Input: nums = [1], k = 1

// Output: [1]

// Example 3:

// Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2

// Output: [1,2]

 

// Constraints:

// 1 <= nums.length <= 105
// -104 <= nums[i] <= 104
// k is in the range [1, the number of unique elements in the array].
// It is guaranteed that the answer is unique.
 

// Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

//   ---------------

// My solution 
//  Use an unordered map to keep the frequency of all nums in array - O(N);
//  Use maxheap to based on frequency to store all nums and their freuncey as a pair.
//  Get the first k elements from top of queue.
//O(n log n) for heap insertion

class Solution {
private:
    struct compare {
        bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second; // max-heap by frequency
        }
    };
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) count[num]++;
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
        for (const auto& entry : count) {
            pq.push({entry.first, entry.second});
        }
        
        vector<int> ans;
        for (int i = 0; i < k; i++) {
            ans.push_back(pq.top().first);
            pq.pop();
        }
        return ans;
    }
};
===================================================

  //Optimized solution using min heap,
  //add numbers to heap of size k, if heapsize goes beyond k, remove the smallest frequency number.

  class Solution {

public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        
        unordered_map<int,int> count;
        for(auto num:nums){
            
                count[num]++;
         
        }
        auto comp = [](const pair<int,int>&a,const pair<int,int>&b){
            return a.second>b.second;
        };
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(comp)>pq(comp);
        for( auto entry : count){
            pq.push({entry.first,entry.second});
            if(pq.size()>k)
                pq.pop();
        }

        vector<int> ans;
        while(!pq.empty()){
            
            ans.push_back(pq.top().first);
            pq.pop();
        }
        return ans;
    }
};
