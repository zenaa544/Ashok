You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {

        using T = tuple<int,int,int>;
        priority_queue<T,vector<T>,greater<T>> minHeap;
        int currentMax=INT_MIN;
        for(int i=0; i< nums.size();i++){

            minHeap.emplace(nums[i][0], i, 0);
            currentMax=max(nums[i][0],currentMax);
        }

        int rangeStart = 0;
        int rangeEnd   =INT_MAX;

        while(true){

            auto [val,row,index ] = minHeap.top();
            minHeap.pop();

            if(currentMax - val < rangeEnd-rangeStart||
               (currentMax-val == rangeEnd-rangeStart && val<rangeStart)){
                rangeStart=val;
                rangeEnd=currentMax;

               }
               if(index+1 < nums[row].size()){
                    minHeap.emplace(nums[row][index+1],row,index+1);
                    currentMax=max(currentMax,nums[row][index+1]);
                }
                else
                    break;
        }
       return {rangeStart,rangeEnd}; 
    }
};
