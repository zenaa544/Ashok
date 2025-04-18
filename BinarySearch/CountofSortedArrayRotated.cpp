class Solution {
  public:
    int findKRotation(vector<int> &arr) {
        // Code Here

	// Write your code here.
    
	int n = arr.size();
    if(n==0) return -1;
	if(n==1) return arr[0];
	int left = 0;
	int right =n-1;
    int ans = INT_MAX;
    int index = -1;
    
	while(left<=right){
     
	 int mid = (left+right)/2;
     
	 if(arr[left]<=arr[mid]){
		 if(arr[left]< ans){
		     index=left;
		     ans= arr[left];
		 }
		 left=mid+1;
	 }
	 else{
		 
		 if(ans> arr[mid]){
		    ans=arr[mid];
		    index= mid;
		 }
		 right = mid-1;
	 }

	}
   return index;


    }
};
