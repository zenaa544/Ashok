Given two sorted arrays a[] and b[] and an element k, the task is to find the element that would be at the kth position of the combined sorted array.

Examples :

Input: a[] = [2, 3, 6, 7, 9], b[] = [1, 4, 8, 10], k = 5
Output: 6
Explanation: The final combined sorted array would be [1, 2, 3, 4, 6, 7, 8, 9, 10]. The 5th element of this array is 6.
Input: a[] = [100, 112, 256, 349, 770], b[] = [72, 86, 113, 119, 265, 445, 892], k = 7
Output: 256
Explanation: Combined sorted array is [72, 86, 100, 112, 113, 119, 256, 265, 349, 445, 770, 892]. The 7th element of this array is 256.


class Solution {
  public:
    int kthElement(vector<int>& arr1, vector<int>& arr2, int k) {
        // code here
    int n=arr1.size();
    int m=arr2.size();
    if (n > m) return kthElement(arr2, arr1,k);

    int low = max(0, k - m);  // cannot pick less than 0 from arr1
    int high = min(n, k);     // cannot pick more than n from arr1

    while (low <= high) {
        int p1 = low + (high - low) / 2;
        int p2 = k - p1;

        int p1MaxL = (p1 == 0) ? INT_MIN : arr1[p1 - 1];
        int p1MinR = (p1 == n) ? INT_MAX : arr1[p1];

        int p2MaxL = (p2 == 0) ? INT_MIN : arr2[p2 - 1];
        int p2MinR = (p2 == m) ? INT_MAX : arr2[p2];

        if (p1MaxL <= p2MinR && p2MaxL <= p1MinR) {
            return max(p1MaxL, p2MaxL);
        } 
        else if (p1MaxL > p2MinR) {
            high = p1 - 1;
        } 
        else {
            low = p1 + 1;
        }
    }
    return -1; // This shouldn't happen if input is valid

    }
};
