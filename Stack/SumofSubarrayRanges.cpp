You are provided with an array of integers called 'nums'. The range of a subarray in ‘nums’ is defined as the difference between 
the largest and smallest element within that subarray.
Your task is to calculate the sum of all the ranges of subarrays in ‘nums’.

A subarray is a contiguous (non-empty) sequence of elements within the original array.

For Example:
Input:[1,2,3]
Output: 4 

  Solution: ans= Sum of SubArray Maximums - Sum of Subarray Minimums;

long long sumMaxSubarray(vector<int>& nums){
    int n=nums.size();
    stack<int> st1;
    stack<int>st2;

    vector<int>prevLessCount(n);
    vector<int>nextLessCount(n);
    
    for(int i=0;i<n;i++){
        while(!st1.empty() && nums[i]>nums[st1.top()]){
            st1.pop();
        }
        prevLessCount[i]= st1.empty()?i+1:i-st1.top();
        st1.push(i);
    }

    for(int i=n-1;i>=0;i--){
        while(!st2.empty() && nums[i]>=nums[st2.top()]){
            st2.pop();
        }

        nextLessCount[i]=st2.empty()?n-i:st2.top()-i;
        st2.push(i);
    }
    long long sum=0;
    for (int i=0;i<n;i++){
         sum+=prevLessCount[i]*nextLessCount[i]*nums[i];
    }
    return sum;
}
long long sumMinSubarray(vector<int>& nums){
    int n=nums.size();
    stack<int> st1;
    stack<int> st2;

    vector<int>prevLessCount(n);
    vector<int>nextLessCount(n);
    
    for(int i=0;i<n;i++){
        while(!st1.empty() && nums[i]<nums[st1.top()]){
            st1.pop();
        }
        prevLessCount[i]= st1.empty()?i+1:i-st1.top();
        st1.push(i);
    }

    for(int i=n-1;i>=0;i--){
        while(!st2.empty() && nums[i]<=nums[st2.top()]){
            st2.pop();
        }

        nextLessCount[i]=st2.empty()?n-i:st2.top()-i;
        st2.push(i);
    }
    long long sum=0;
    for (int i=0;i<n;i++){
         sum+=prevLessCount[i]*nextLessCount[i]*nums[i];
    }
    return sum;
}
int rangeSum(vector<int>&nums){
    // Write your code here.

   

    long long sumMins=sumMinSubarray(nums);
    long long  sumMaxs=sumMaxSubarray(nums);

    return (int)(sumMaxs-sumMins);
}
