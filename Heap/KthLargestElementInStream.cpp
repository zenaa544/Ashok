Given an input stream arr[] of n integers. Find the Kth largest element (not Kth largest unique element) after insertion of each element in the stream 
and if the Kth largest element doesn't exist, the answer will be -1 for that insertion. 
return a list of size n after all insertions.


Solution:
Use a min heap to keep the elements from array, 
limit the size of min heap to k , 
top element of min heap will always be kth largest element
if size of heap is less than k , then kth largest does not exist yet.

class Solution {
  public:
    vector<int> kthLargest(int k, int arr[], int n) {
        // code here
        priority_queue<int, vector<int> ,greater<int>>minHeap;
        
        vector<int>result;
        
        for(int i=0;i< n;i++ ){
            
          minHeap.push(arr[i]);
          
          if(minHeap.size()>k)
            minHeap.pop();
            
          if(minHeap.size()<k){
              result.push_back(-1);
          } 
          else{
              result.push_back(minHeap.top());
          }
        }
        return result;
    }
};
