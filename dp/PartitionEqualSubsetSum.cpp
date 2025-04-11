/* https://leetcode.com/problems/subarray-sum-equals-k/description/

Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.
 
Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.

*/
class Solution {
public:
    bool solve(vector<int>& nums, int index, int target){
        if(target==0) return true;

        if(index>=nums.size())return false;
        return(solve(nums,index+1,target)||solve(nums,index+1,target-nums[index]));

 

    }
   bool solveMem(vector<int>& nums, int index, int target, vector<vector<int>>& dp) {
        if (target == 0) return true;
        if (index >= nums.size() || target < 0) return false;

        if (dp[index][target] != -1) return dp[index][target];

        bool take = solveMem(nums, index + 1, target - nums[index], dp);
        bool notTake = solveMem(nums, index + 1, target, dp);

        dp[index][target] = take || notTake;
        return dp[index][target];
    }
  
  bool solveTab(vector<int>& nums, int n, int target){

     // dp[i][j] = true if we can get sum j using first i elements
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        // Base case: sum 0 is always possible (empty subset)
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= target; j++) {
                bool notTake = dp[i - 1][j];
                bool take = false;
                if (nums[i - 1] <= j)
                    take = dp[i - 1][j - nums[i - 1]];
                dp[i][j] = take || notTake;
            }
        }

        return dp[n][target];
     }
  

    bool canPartition(vector<int>& nums) {
        
       int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        int target = sum / 2;
        int n = nums.size();


        return solveTab(nums,n,target);
     }
};
