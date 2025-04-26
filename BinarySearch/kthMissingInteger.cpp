Kth Missing Positive Number
Easy
Topics
Companies
Hint
Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.

Return the kth positive integer that is missing from this array.

  int missingCount(const std::vector<int>& arr, int index) {
    return arr[index] - arr[0] - index;
}

int findKthMissing(const std::vector<int>& arr, int k) {
    int n = arr.size();
    
    // If k is greater than total missing till the end, return beyond the last element
    if (missingCount(arr, n - 1) < k)
        return arr[n - 1] + (k - missingCount(arr, n - 1));
    
    int left = 0, right = n - 1;
    
    // Binary search for the smallest index such that missingCount(index) >= k
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (missingCount(arr, mid) < k)
            left = mid + 1;
        else
            right = mid;
    }
    
    // The kth missing number lies between arr[left - 1] and arr[left]
    return arr[left - 1] + (k - missingCount(arr, left - 1));
}

===================================================

class Solution {
public:
  int findKthPositive(vector<int>& arr, int k) {
    int low = 0;
    int high = arr.size() - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int missing = arr[mid] - (mid + 1);
        
        if (missing < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // After loop, low is the number of elements present before kth missing
    // So answer is: low + k
    return low + k;
}
};

=========================================
int findKthPositive(vector<int>& arr, int k) {
    for (int num : arr) {
        if (num <= k) {
            k++;
        } else {
            break;
        }
    }
    return k;
}

