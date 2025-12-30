You are given an integer array arr[]. You need to find the maximum sum of a subarray (containing at least one element) in the array arr[].

Note : A subarray is a continuous part of an array.

Can find the max sum also the subarray.
  1. Intuition Behind Kadane's Algorithm
The Problem
Given an array, find the contiguous subarray with the largest sum (could have negatives).

Key Observations
If adding an element increases your current sum, your subarray is getting better.
If adding it decreases or makes your sum negative, you should "start over".
At each point, the best sum ending here is either:
This element alone
Or, extending the previous best subarray sum by including this element
Analogy
Imagine walking across stones with some positive/negative values. Every step, you decide:

"Should I keep hopping from the last stone?"
Or "Is it better to just start fresh on this stone and ignore the past?"
If you always keep track of the best sum seen so far, then after all stones, you have your answer.

2. Two Popular Kadane's Implementations
A. max(cur_sum + arr[i], arr[i]) Version (Classic Formulation)
At each index, compute:
curr_sum = max(arr[i], curr_sum + arr[i])
Do I start new here? If yes, arr[i]
Do I continue the existing sum? If yes, curr_sum + arr[i]
Update the global max:
max_so_far = max(max_so_far, curr_sum)
Why?

You're always choosing at each step whether to start a fresh subarray or continue.

If everything before made the sum negative, starting over (with arr[i]) is better!

B. Reset on Negatives Version
Maintain a running sum curr_sum
If curr_sum < 0, set curr_sum = 0 (starting a new subarray from next element)
Update global maximum if the new sum is bigger.
Why?

If your sum goes negative, every subarray including that negative bit will be worse than starting at the next element.

So, as soon as you dip below zero, reset.

Visualize:

Positive hills help climb higher. Negative valleys drag you down. So you restart after a valley if it drops you below ground level.

Tracking the Subarray (Indices)
Both methods can be enhanced to track where the subarray started and ended by:

Remembering where you last reset
Marking indices when a new max is found
Summary
Kadane's intuition: At each element, decide to continue or restart.
Every implementation fundamentally answers: "Is my future brighter if I leave the past behind and start now?"
Resets happen when your current sum hurts your chances.
You can always track the best interval (indices) by marking where you reset and where you find the new max.
Final Thought
Both approaches are just two sides of the same coin.

They greedily ensure you don't carry negative baggage into your subarray,

so you only pick the stretches that increase your maximum sum.




  class Solution {
  public:
    int maxSubarraySum(vector<int> &arr) {
        // Code here
        
        int sum = 0;
        int maxS= INT_MIN;
        
        for(int i=0;i<arr.size();i++){
            
            sum= sum+arr[i];

        
            if(sum > maxS) maxS=sum;
            if(sum<0) sum =0;
        }
        
        return maxS;
    }
};
==============================================
  class Solution {
  public:
    int maxSubarraySum(vector<int> &arr) {
        // Code here
        
        int sum = arr[0];
        int maxS=sum;
        
        for(int i=1;i<arr.size();i++){
            
            sum= max(arr[i],sum+arr[i]);

            maxS=max(sum,maxS);
            
        }
        
        return maxS;
    }
};
=====================================================


  FInding the subarray

#include <vector>
#include <iostream>
using namespace std;

pair<int, pair<int, int>> maxSubarraySumWithIndices(const vector<int>& arr) {
    int currSum = 0, maxSum = INT_MIN;
    int start = 0, end = 0, s = 0; // s: candidate start

    for (int i = 0; i < arr.size(); ++i) {
        currSum += arr[i];

        if (currSum > maxSum) {
            maxSum = currSum;
            start = s;
            end = i;
        }

        if (currSum < 0) {
            currSum = 0;
            s = i + 1; // candidate for new subarray start
        }
    }
    return {maxSum, {start, end}};
}

int main() {
    vector<int> arr = {1, 2, 3, -2, 5};

    auto result = maxSubarraySumWithIndices(arr);
    int maxSum = result.first;
    int start = result.second.first;
    int end = result.second.second;

    cout << "Max Subarray Sum: " << maxSum << endl;
    cout << "Subarray: ";
    for (int i = start; i <= end; ++i)
        cout << arr[i] << " ";
    cout << endl;
    // Output: Max = 9, subarray = 1 2 3 -2 5
}
=================================================
  pair<int, pair<int, int>> maxSubArrayWithIndices(const vector<int>& nums) {
    int max_so_far = nums[0], curr_max = nums[0];
    int start = 0, end = 0, s = 0;

    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] > curr_max + nums[i]) {
            curr_max = nums[i];
            s = i; // Start a new subarray
        } else {
            curr_max += nums[i];
        }

        if (curr_max > max_so_far) {
            max_so_far = curr_max;
            start = s;   // update start
            end = i;     // update end
        }
    }
    // Returns max sum and indices (start, end)
    return {max_so_far, {start, end}};
}
