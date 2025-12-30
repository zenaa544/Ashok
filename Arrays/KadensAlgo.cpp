You are given an integer array arr[]. You need to find the maximum sum of a subarray (containing at least one element) in the array arr[].

Note : A subarray is a continuous part of an array.

Can find the max sum also the subarray.


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
