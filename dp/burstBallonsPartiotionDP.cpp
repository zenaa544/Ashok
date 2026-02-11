312. Burst Balloons
Hard
Topics
premium lock icon
Companies
You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.

If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.

 

Example 1:

Input: nums = [3,1,5,8]
Output: 167
Explanation:
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
Example 2:

Input: nums = [1,5]
Output: 10
 

Constraints:

n == nums.length
1 <= n <= 300
0 <= nums[i] <= 100

===================================
  Burst Balloons DP Approach — “If I want max coins in (left, right)”
Define the main subproblem:

If I want to get the maximum coins by bursting all balloons in interval (left, right) (that is, excluding left and right),
I’ll call dp[left][right] the answer to this subproblem.
Reduction Step (Partition):

Suppose I choose the k-th balloon (left < k < right) as the last balloon to burst in this interval.
Bursting k last gives coins = nums[left] * nums[k] * nums[right]
Before bursting k, I can independently burst all balloons in:
(left, k) (left of k), which is dp[left][k]
(k, right) (right of k), which is dp[k][right]
The total coins if I burst k last:
css
Copy code
dp[left][k] + nums[left]*nums[k]*nums[right] + dp[k][right]
Try all possible k for (left, right):

For every possible k in (left, right), find the maximum result.
css
Copy code
dp[left][right] = max over all k in (left, right)
                  of (dp[left][k] + nums[left] * nums[k] * nums[right] + dp[k][right])
Base case:

If (left, right) are adjacent (i.e., left + 1 == right),
There are no balloons to burst; so dp[left][right] = 0.
Summary Formula:
For every interval (left, right):

css
Copy code
dp[left][right] = max {
    dp[left][k] + nums[left] * nums[k] * nums[right] + dp[k][right]
    for all k in (left, right)
}

dp[left][right] = 0, if left + 1 == right
Implementation note:
Add 1 at both ends of the original array for padding, to simplify edge handling.
Bottom-up: Fill dp[left][right] for all intervals of increasing length.
Final answer is dp[0][n+1] (all original balloons between virtual boundaries).
If you want max coins in (left, right):
Assume for each k in (left, right) you burst k last,
Combine coins from independent left and right intervals,
Add the coins from bursting k with its current neighbors,
Maximize over all such k.

===================================================

brute force

int solve(int left, int right, vector<int>& nums) {
    // base case: no balloon between left and right
    if (left + 1 == right) return 0;

    int maxCoins = 0;
    // Try bursting each balloon in (left, right) last
    for (int k = left + 1; k < right; ++k) {
        int coins = 
            solve(left, k, nums) +                  // burst [left+1, k-1]
            solve(k, right, nums) +                 // burst [k+1, right-1]
            nums[left] * nums[k] * nums[right];     // burst k last
        maxCoins = max(maxCoins, coins);
    }
    return maxCoins;
}

int maxCoins(vector<int>& nums) {
    int n = nums.size();
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    // Solve for [0, n+1], so real indices are 1...n
    return solve(0, n + 1, nums);
}
 ========================================================== 
memoization
  int solve(int left, int right, vector<int>& nums, vector<vector<int>>&dp) {
    // base case: no balloon between left and right
    if (left + 1 == right) return 0;
    if (dp[left][right]!=-1) return dp[left][right];
    int maxCoins = 0;
    // Try bursting each balloon in (left, right) last
    for (int k = left + 1; k < right; ++k) {
        int coins = 
            solve(left, k, nums) +                  // burst [left+1, k-1]
            solve(k, right, nums) +                 // burst [k+1, right-1]
            nums[left] * nums[k] * nums[right];     // burst k last
        maxCoins = max(maxCoins, coins);
    }
    return dp[left][right]= maxCoins;
}

=========================
  bottom up tabulation
int maxCoins(vector<int>& nums) {
    int n = nums.size();
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
	vector<vector<int>>dp(n+2,vector<int>(n+2,-1));
    // Solve for [0, n+1], so real indices are 1...n
    return solve(0, n + 1, nums,dp);
}
=========================================

int maxCoins(vector<int> & nums){
    int n = nums.size();
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    // len = interval length
    for (int len = 2; len <= n + 1; ++len) { // interval size
        for (int left = 0; left + len <= n + 1; ++left) {
            int right = left + len;
            for (int k = left + 1; k < right; ++k) {
                dp[left][right] = max(
                    dp[left][right],
                    dp[left][k] + dp[k][right] + nums[left]*nums[k]*nums[right]
                );
            }
        }
    }
    return dp[0][n + 1];
}
  
