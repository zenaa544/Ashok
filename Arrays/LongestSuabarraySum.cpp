//Find length of longest subarray with sum==k- Prefixsum method, Used when array conatins _ve,0s and -ve
//Use 2 pointer for only +vesand 0s

int getLongestSubarray(vector<int>& nums, int k){
    unordered_map<int, int> prefixSum;
    int length = 0;
    int maxLength = 0;
    long long sum = 0;

    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];

        if (sum == k) {
            length = i + 1;
            maxLength = max(length, maxLength);
        }

        if (prefixSum.find(sum - k) != prefixSum.end()) {
            length = i - prefixSum[sum - k];
            maxLength = max(length, maxLength);
        }

        // Only store the first occurrence of each sum
        if (prefixSum.find(sum) == prefixSum.end()) {
            prefixSum[sum] = i;
        }
    }

    return maxLength;
}
