Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.


  
  
long long totalHours(const vector<int>& piles, int bananasPerHour) {
        long long total = 0;
        for (int i = 0; i < piles.size(); i++) {
            total += (piles[i] + bananasPerHour - 1) / bananasPerHour;
        }
        return total;
    }
int minimumRateToEatBananas(vector<int> piles, int h) {
    // Write Your Code Here
    if (piles.empty()) return 0;

        int low = 1;
        int high = *max_element(piles.begin(), piles.end());
        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (totalHours(piles, mid) <= h) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    
}
