A conveyor belt has packages that must be shipped from one port to another within days days.

The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.

Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.

class Solution {
public:
    int daysNeeded(vector<int>& weights, int capacity){
     
      int days=1;
      int load=0;

      for(auto weight: weights){
             //load+=weight;
             if(load+weight>capacity){
                days++;
                load=weight;
             }
             else{
                load+=weight;
             }
      }
    return days;

    }
    int shipWithinDays(vector<int>& weights, int days) {
            int low = *max_element(weights.begin(), weights.end()); // Cannot be less than heaviest package
    int high = 0;
    for (int w : weights) high += w;
    
    int ans = high;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (daysNeeded(weights, mid) <= days) {
            ans = mid;  // Possible, try smaller capacity
            high = mid - 1;
        } else {
            low = mid + 1; // Not enough, try bigger capacity
        }
    }
    
    return ans;
    }
};
