Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. 
Since the answer may be large, return the answer modulo 109 + 7.


Solution :
For each element:

Find how many elements to the left are greater than or equal (strictly greater for uniqueness) — call this left.

Find how many elements to the right are strictly greater — call this right.

The total number of subarrays in which arr[i] is the minimum is:
left_count * right_count



 int sumSubarrayMins(vector<int>& arr) {

    const int MOD = 1e9 + 7;
    int n =arr.size();

    vector<int> prevLess(n);
    vector<int> nextLess(n);

    stack <int> st1;
    stack <int> st2;
    long long  sum=0;
    //count previous elements that are less than each element and store in prevLess
    //it includes current element
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

 
