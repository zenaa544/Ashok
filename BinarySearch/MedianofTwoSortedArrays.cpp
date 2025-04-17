Idea is to first find what could be possible median index , (n1+n2)/2  if total odd elements else meed to pick both elements arround (n1+n2)/2

  if we take (n1+n2)/2 elements how many of this can be from n1 array and how many from n2 array till we find a prefect condition
where they can be sorted.

  
//for logn solution pick the smaller array and do binary search on it.

double solve(vector<int>& nums1, vector<int>& nums2, int n1, int n2) {

        if (n1 > n2)
            return solve(nums2, nums1, n2, n1);

        int low = 0;
        int high = n1;

        while (low <= high) {
            int p1 = (low + high) / 2;
            int p2 = (n1 + n2 + 1) / 2 - p1;

            int maxL1 = p1 <= 0 ? INT_MIN : nums1[p1 - 1];
            int minR1 = p1 >= n1 ? INT_MAX : nums1[p1];

            int maxL2 = p2 <= 0 ? INT_MIN : nums2[p2 - 1];
            int minR2 = p2 >= n2 ? INT_MAX : nums2[p2];

            if (maxL1 <= minR2 && minR1 > maxL2) {

                if ((n1 + n2) % 2 == 0) {
                    return (double(double(max(maxL1, maxL2)) +
                                   double(min(minR1, minR2))) /
                            2.0);

                } else
                    return double(max(maxL1, maxL2));
            }
            if (maxL1 > minR2) {
                high = p1 - 1;

            } else {
                low = p1 + 1;\
            }
        }
        return double(0);
    }
double median(vector<int>& nums1, vector<int>& nums2) {
	// Write your code here.
		int n1 = nums1.size();
        int n2 = nums2.size();

        return solve(nums1, nums2, n1, n2);


}
