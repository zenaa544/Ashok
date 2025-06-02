Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. 
Since the answer may be large, return the answer modulo 109 + 7.


Solution :
💡 Key Idea
For each element arr[i], count how many subarrays exist where arr[i] is the minimum.
Then multiply arr[i] with the number of such subarrays to get its total contribution.

✅ How to Count Subarrays Where arr[i] is the Minimum
Use monotonic stacks to compute:

prevLess[i]:
Number of elements to the left of i (including i) such that all are greater than arr[i]
→ These are the subarrays that can start from a previous index and end at i.

nextLess[i]:
Number of elements to the right of i (including i) such that all are greater than or equal to arr[i]
→ These are the subarrays that can start at i and end at a later index.

So total number of subarrays where arr[i] is the minimum = prevLess[i] * nextLess[i].

🧮 Final Formula

sum += arr[i] * prevLess[i] * nextLess[i];


📦 Time and Space Complexity
Time: 
𝑂(𝑛)
O(n) — each element is pushed and popped from the stack once.

Space: 
𝑂(𝑛)
O(n) — for prevLess, nextLess, and stacks.



 int sumSubarrayMins(vector<int>& arr) {

    const int MOD = 1e9 + 7;
    int n =arr.size();

    vector<int> prevLess(n);
    vector<int> nextLess(n);

    stack <int> st1;
    stack <int> st2;
    long long  sum=0;
    //We are counting number of subarrays where current element is the minimum, for that we are checking 
    //How many elements to the left are greater than current element and howmany to to the right are greater than current element
    for(int i=0;i<n;++i){
        while(!st1.empty() && arr[i]< arr[st1.top()]){
            st1.pop();
        }

        prevLess[i]=st1.empty()? i+1:i-st1.top();
        st1.push(i);
    }
    
    //Count how many next elements are smaller than each element and store in nextLess
    //it excludes the current element;
    for(int i=n-1;i>=0;--i){
        while(!st2.empty() && arr[i]<=arr[st2.top()]){
            st2.pop();
        }

        nextLess[i]=st2.empty()?n-i:st2.top()-i;
        st2.push(i);
    }
   
   for(int i=0;i<n;i++){
       long long currentSum= (long long) prevLess[i]*nextLess[i]*arr[i];
       sum= (sum+currentSum) % MOD;
   }
   return sum;

        
    }
};

 
