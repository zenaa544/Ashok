//count all subarrays that sum upto target K
//Use prefix sum and map to keep the count of subarrays for a sum;

int findAllSubarraysWithGivenSum(vector < int > & nums, int k) {
    // Write Your Code Here
     
        unordered_map<int,int>prefixSum;
        int count=0;
        int sum=0;
        for(int i=0;i<nums.size();i++){
            sum=sum+nums[i];

            if(sum==k)count++;

            if(prefixSum.find(sum-k)!=prefixSum.end())
                count+=prefixSum[sum-k];
                
            prefixSum[sum]++;
        }
        return count;
}
