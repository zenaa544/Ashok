Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.


  class Solution {
public:

    vector<int> searchRange(vector<int>& nums, int target) {
    
    if(!nums.size()){return {-1,-1};}
     int start = -1; int end= -1;

     int left=0; int right = nums.size()-1;

     while(left<=right){
       
       int mid = (left+right)/2;

       if(nums[mid]==target){
         start=mid;
         right=mid-1;
       }
       else if(nums[mid]>target){
        right=mid-1;
       }
       else
         left=mid+1;

     }  

     if (start==-1) return {-1,-1};

      left = 0;
      right = nums.size() - 1;
      while(left<=right){
       
       int mid = (left+right)/2;

       if(nums[mid]==target){
         end=mid;
         left=mid+1;
       }
       else if(nums[mid]>target){
        right=mid-1;
       }
       else
         left=mid+1;

     }  
    
    
    return {start,end};
    }
};
