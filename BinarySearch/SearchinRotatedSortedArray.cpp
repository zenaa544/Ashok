int search(int* nums, int n, int target) {
    // Write your code here.
      int left = 0;
        int right = n - 1;

        while (left <= right) {

            int mid = (left + right) / 2;

            if (nums[mid] == target)
                return mid;

            if (nums[mid] >= nums[left]) {
                if (target >= nums[left] && target <= nums[mid]){
                    right = mid - 1;
                } 
                else {
                    left = mid + 1;
                }
            }
            else {
                if (nums[mid] <= target && target <= nums[right]) {
                    left = mid + 1;
                
                }
                else {
                    right = mid - 1;
                }
            }
        } 
        return -1;
    


}
